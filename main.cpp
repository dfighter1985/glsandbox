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

#include <iostream>

#include "ExampleApplication.h"

ExampleApplication app;

void ChangeSize( int w, int h )
{
	app.onResizeWindow( w, h );
}

void RenderScene()
{
	app.render();
}

int main( int argc, char **argv )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize( 800, 600 );
	glutCreateWindow( "Example GLUT Application" );

	glutReshapeFunc( ChangeSize );
	glutDisplayFunc( RenderScene );

	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		std::cerr << "GLEW Error: " << glewGetErrorString( err ) << std::endl;
		return 1;
	}

	app.setup();
	glutMainLoop();

	return 0;
}