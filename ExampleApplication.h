#ifndef EXAMPLEAPP_H
#define EXAMPLEAPP_H

#include "GLUTApplication.h"

class VertexBuffer;
class Texture;

class ExampleApplication : public GLUTApplication
{
public:
	ExampleApplication();
	~ExampleApplication();
	void setup();
	void onResizeWindow( int w, int h );
	void onKeyDown( unsigned char key, int mouseX, int mouseY );
	void render();

private:
	VertexBuffer *vbo;
	VertexBuffer *floorVBO;
	Texture *texture;
	Texture *floorTexture;
	float z;
};

#endif

