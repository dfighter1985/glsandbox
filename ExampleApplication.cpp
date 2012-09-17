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

#include "VertexBuffer.h"
#include "ShaderManager.h"


GLfloat vertices[] =
{
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
};

ShaderManager shaderManager;

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

	shaderManager.loadShaderFiles( "red", "shaders/red.vp", "shaders/red.fp" );
	shaderManager.useProgram( "red" );
}

void ExampleApplication::onResizeWindow( int w, int h )
{
	glViewport( 0, 0, w, h );
}

void ExampleApplication::render()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	vbo->draw( GL_TRIANGLE_FAN );
	glutSwapBuffers();
}

