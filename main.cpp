#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#ifndef FREEGLUT_STATIC
#define FREEGLUT_STATIC
#endif
#include <gl/glew.h>
#include <gl/gl.h>		
#include <GL/glut.h>
#include <iostream>
#include "ExampleApplication.h"

ExampleApplication app;

void onResizeWindow( int w, int h )
{
	app.onResizeWindow( w, h );
}

void onKeyDown( unsigned char k, int mouseX, int mouseY )
{
	app.onKeyDown( k, mouseX, mouseY );
}

void onRenderScene()
{
	app.render();
}

int main( int argc, char **argv )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize( 800, 600 );
	glutCreateWindow( "Example GLUT Application" );

	glutReshapeFunc( onResizeWindow );
	glutDisplayFunc( onRenderScene );
	glutKeyboardFunc( onKeyDown );

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
