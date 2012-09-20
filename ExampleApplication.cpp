#include "ExampleApplication.h"

#include <windows.h>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <gl/glew.h>
#include <gl/gl.h>		

#ifndef FREEGLUT_STATIC
#define FREEGLUT_STATIC
#endif
#include <GL/glut.h>

#include <cassert>
#include "VertexBuffer.h"
#include "ShaderManager.h"
#include "Math3D.h"
#include "Frustum.h"
#include "TransformPipeline.h"


GLfloat vertices[] =
{
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
};

ShaderManager shaderManager;
MatrixStack mv;
Frustum p;
TransformPipeline pipeline;

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
	vbo->buffer( 4, vertices, NULL, NULL );

	shaderManager.loadShaderFiles( "red", "shaders/red_trans.vp", "shaders/red.fp" );
	shaderManager.useProgram( "red" );

	mv.loadIdentity();
	mv.translate( 0.0f, 0.0f, -0.5f );

	pipeline.setup( &mv, &p );
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

	glutPostRedisplay();
}

void ExampleApplication::render()
{
	mv.push();

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	mv.translate( 0.0f, 0.0f, z );
	
	GLint mvpLocation = glGetUniformLocation( shaderManager.getCurrentProgramId(), "mvp" );
	if( mvpLocation == -1 )
		assert( false );
	glUniformMatrix4fv( mvpLocation, 1, GL_FALSE, pipeline.getMVPMatrix() );

	vbo->draw( GL_TRIANGLE_FAN );
	glutSwapBuffers();
	
	mv.pop();
}

