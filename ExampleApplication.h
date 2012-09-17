#ifndef EXAMPLEAPP_H
#define EXAMPLEAPP_H

#include "GLUTApplication.h"

class VertexBuffer;

class ExampleApplication : public GLUTApplication
{
public:
	ExampleApplication();
	~ExampleApplication();
	void setup();
	void onResizeWindow( int w, int h );
	void render();

private:
	VertexBuffer *vbo;
};

#endif

