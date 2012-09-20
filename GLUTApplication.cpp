#include "GLUTApplication.h"

#ifndef FREEGLUT_STATIC
#define FREEGLUT_STATIC
#endif
#include <GL/glut.h>

void GLUTApplication::swapBuffers()
{
	glutSwapBuffers();
}

void GLUTApplication::postRedisplay()
{
	glutPostRedisplay();
}
