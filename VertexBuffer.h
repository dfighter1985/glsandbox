#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void buffer( unsigned long n, void *vertices, void *texCoords, void *normals );
	void draw();

private:
	bool vBuffered;
	bool tBuffered;
	bool nBuffered;

	unsigned int vId;
	unsigned int tId;
	unsigned int nId;
	unsigned long size;
};

#endif

