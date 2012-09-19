#include "ExampleApplication.h"

#include <windows.h>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <gl\glew.h>
#include <gl\gl.h>		

#ifndef FREEGLUT_STATIC
#define FREEGLUT_STATIC
#endif
#include <GL/glut.h>

#include <cassert>
#include "VertexBuffer.h"
#include "ShaderManager.h"
#include "Math3D.h"


GLfloat vertices[] =
{
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
};

ShaderManager shaderManager;
MatrixStack stack;

ExampleApplication::ExampleApplication()
{
	vbo = NULL;
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

	stack.loadIdentity();
	stack.scale( 0.5f, 0.5f, 0.5f );
	stack.rotate( 30, 0.0f, 0.0f, 1.0f );
	stack.translate( 0.5f, 0.5f, 0.0f );

}

void ExampleApplication::onResizeWindow( int w, int h )
{
	glViewport( 0, 0, w, h );
}

void ExampleApplication::render()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	GLint mvpLocation = glGetUniformLocation( shaderManager.getCurrentProgramId(), "mvp" );
	if( mvpLocation == -1 )
		assert( false );
	glUniformMatrix4fv( mvpLocation, 1, GL_FALSE, stack.top().getAsArray() );

	vbo->draw( GL_TRIANGLE_FAN );
	glutSwapBuffers();
}

