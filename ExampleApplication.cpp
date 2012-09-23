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
#include "Texture2D.h"
#include "CubeMapTexture.h"

GLfloat floorVertices[] =
{
	-20.0f, 0.0f, -20.0f,
	-20.0f, 0.0f, 20.0f,
	20.0f, 0.0f, 20.0f,
	20.0f, 0.0f, -20.0f
};

GLfloat floorTexCoords[] =
{
	0.0f, 0.0f,
	0.0f, 20.0f,
	20.0f, 20.0f,
	20.0f, 0.0f
};

GLfloat boxTexCoords[] =
{
	//front
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f
};

GLfloat boxVertices[] =
{
	// front
	-0.5f, 1.0f, 0.0f,
	-0.5f, 0.0f, 0.0f,
	0.5f, 0.0f, 0.0f,
	0.5f, 0.0f, 0.0f,
	0.5f, 1.0f, 0.0f,
	-0.5f, 1.0f, 0.0f,
	//back
	-0.5f, 1.0f, -1.0f,
	-0.5f, 0.0f, -1.0f,
	0.5f, 0.0f, -1.0f,
	0.5f, 0.0f, -1.0f,
	0.5f, 1.0f, -1.0f,
	-0.5f, 1.0f, -1.0f,
	// left
	-0.5f, 1.0f, -1.0f,
	-0.5f, 0.0f, -1.0f,
	-0.5f, 0.0f, 0.0f,
	-0.5f, 0.0f, 0.0f,
	-0.5f, 1.0f, 0.0f,
	-0.5f, 1.0f, -1.0f,
	// right
	0.5f, 1.0f, -1.0f,
	0.5f, 0.0f, -1.0f,
	0.5f, 0.0f, 0.0f,
	0.5f, 0.0f, 0.0f,
	0.5f, 1.0f, 0.0f,
	0.5f, 1.0f, -1.0f,
	// top
	-0.5f, 1.0f, -1.0f,
	-0.5f, 1.0f, 0.0f,
	0.5f, 1.0f, 0.0f,
	0.5f, 1.0f, 0.0f,
	0.5f, 1.0f, -1.0f,
	-0.5f, 1.0f, -1.0f,
	// bottom
	-0.5f, 0.0f, -1.0f,
	-0.5f, 0.0f, 0.0f,
	0.5f, 0.0f, 0.0f,
	0.5f, 0.0f, 0.0f,
	0.5f, 0.0f, -1.0f,
	-0.5f, 0.0f, -1.0f
};

GLfloat boxNormals[] =
{
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,

	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f
};

ShaderManager shaderManager;
MatrixStack mv;
Frustum p;
TransformPipeline pipeline;

ExampleApplication::ExampleApplication()
{
	boxVBO = NULL;
	floorVBO = NULL;
	boxTexture = NULL;
	floorTexture = NULL;
	z = 0.0f;
	x = 0.0f;
	yRot = 0.0f;
}

ExampleApplication::~ExampleApplication()
{
	delete boxVBO;
	boxVBO = NULL;
	delete floorVBO;
	floorVBO = NULL;
	delete boxTexture;
	boxTexture = NULL;
	delete floorTexture;
	floorTexture = NULL;
}

void ExampleApplication::setup()
{
	glEnable( GL_DEPTH_TEST );
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	
	boxVBO = new VertexBuffer();
	boxVBO->buffer(  36, boxVertices, boxTexCoords, boxNormals  );

	floorVBO = new VertexBuffer();
	floorVBO->buffer( 4, floorVertices, floorTexCoords, NULL );

	bool ok = shaderManager.loadShaderFiles( "tex", "shaders/tex.vp", "shaders/tex.fp" );
	assert( ok );

	shaderManager.useProgram( "tex" );

	mv.loadIdentity();
	mv.translate( 0.0f, -0.5f, -0.5f );

	pipeline.setup( &mv, &p );

	TGAFile f;
	ok = f.load( "wood.tga" );
	assert( ok );

	boxTexture = new Texture2D();
	boxTexture->bind( 0 );
	boxTexture->loadImage( *f.getImage() );

	f.clear();
	ok = f.load( "floor.tga" );
	assert( ok );

	floorTexture = new Texture2D();
	floorTexture->bind( 0 );
	floorTexture->loadImage( *f.getImage() );
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
		z += 0.1f;
		break;
	case 's':
		z -= 0.1f;
		break;
	case 'q':
		x += 0.1f;
		break;
	case 'e':
		x -= 0.1f;
		break;
	case 'a':
		yRot += 5.0f;
		break;
	case 'd':
		yRot -= 5.0f;
		break;
	}

	postRedisplay();
}

void ExampleApplication::render()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	mv.push();
	mv.rotate( yRot, 0.0f, 1.0f, 0.0f );
	mv.translate( x, 0.0f, z );

	shaderManager.useProgram( "tex" );
	GLint mvpLocation = glGetUniformLocation( shaderManager.getCurrentProgramId(), "mvp" );
	assert( mvpLocation != -1 );
	GLint samplerLocation = glGetUniformLocation( shaderManager.getCurrentProgramId(), "sampler" );
	assert( samplerLocation != -1 );
	glUniformMatrix4fv( mvpLocation, 1, GL_FALSE, pipeline.getMVPMatrix() );
	glUniform1i( samplerLocation, 0 );

	floorTexture->bind( 0 );
	floorVBO->draw( GL_TRIANGLE_FAN );

	boxTexture->bind( 0 );
	boxVBO->draw();

	mv.pop();
	swapBuffers();
}

