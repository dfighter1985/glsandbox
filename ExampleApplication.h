#ifndef EXAMPLEAPP_H
#define EXAMPLEAPP_H

#include "GLUTApplication.h"

class VertexBuffer;
class Texture2D;
class CubeMapTexture;

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
	VertexBuffer *floorVBO;
	VertexBuffer *boxVBO;
	Texture2D *boxTexture;
	Texture2D *floorTexture;
	float x;
	float y;
	float z;
	float yRot;
};

#endif

