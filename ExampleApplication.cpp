#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <gl/glew.h>
#include <gl/gl.h>
#include <cassert>
#include "VertexBuffer.h"
#include "ShaderManager.h"
#include "Math3D.h"
#include "Frustum.h"
#include "TransformPipeline.h"
#include "ExampleApplication.h"
#include "TGAFile.h"
#include "Texture.h"

GLfloat vertices[] =
{
	-0.5f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f
};

GLfloat texCoords[] =
{
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f
};

ShaderManager shaderManager;
MatrixStack mv;
Frustum p;
TransformPipeline pipeline;
Texture texture;

ExampleApplication::ExampleApplication()
{
	vbo = NULL;
	z = 0.0f;
}

ExampleApplication::~ExampleApplication()
{
	delete vbo;
	vbo = NULL;
}

void ExampleApplication::setup()
{
	glEnable( GL_DEPTH_TEST );
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	
	vbo = new VertexBuffer();
	vbo->buffer( 4, vertices, texCoords, NULL );

	bool ok = shaderManager.loadShaderFiles( "tex", "shaders/tex.vp", "shaders/tex.fp" );
	assert( ok );

	shaderManager.useProgram( "tex" );

	mv.loadIdentity();
	mv.translate( 0.0f, 0.0f, -0.5f );

	pipeline.setup( &mv, &p );

	TGAFile f;
	ok = f.load( "opengl.tga" );
	if( !ok )
		assert( false );

	texture.bind( 0 );
	texture.loadImage( *f.getImage() );
}

void ExampleApplication::onResizeWindow( int w, int h )
{
	glViewport( 0, 0, w, h );
	p.perspective( 90.0f, w/(float)h, 0.01f, 1000.0f );
}

void ExampleApplication::onKeyDown( unsigned char key, int mouseX, int mouseY )
{
	switch( key )
	{
	case 'w':
		z -= 0.1f;
		break;
	case 's':
		z += 0.1f;
		break;
	}

	postRedisplay();
}

void ExampleApplication::render()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	mv.push();
	mv.translate( 0.0f, 0.0f, z );

	texture.bind( 0 );
	
	GLint mvpLocation = glGetUniformLocation( shaderManager.getCurrentProgramId(), "mvp" );
	assert( mvpLocation != -1 );
	GLint samplerLocation = glGetUniformLocation( shaderManager.getCurrentProgramId(), "sampler" );
	assert( samplerLocation != -1 );

	glUniformMatrix4fv( mvpLocation, 1, GL_FALSE, pipeline.getMVPMatrix() );
	glUniform1ui( samplerLocation, 0 );

	vbo->draw( GL_TRIANGLE_FAN );

	mv.pop();
	swapBuffers();
}

