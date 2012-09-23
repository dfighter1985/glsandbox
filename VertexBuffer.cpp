#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#ifndef FREEGLUT_STATIC
#define FREEGLUT_STATIC
#endif

#include <gl/glew.h>
#include <gl/gl.h>		
#include <GL/glut.h>

#include <cassert>
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	size = 0;
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	GLuint Ids[ 3 ];

	glGenBuffers( 3, Ids );
	if( Ids[ 0 ] == 0 || Ids[ 1 ] == 0 || Ids[ 2 ] == 0 )
		assert( false );
	
	vId = Ids[ 0 ];
	tId = Ids[ 1 ];
	nId = Ids[ 2 ];

	glBindBuffer( GL_ARRAY_BUFFER, vId );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	glBindBuffer( GL_ARRAY_BUFFER, tId );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, 0 );
	glBindBuffer( GL_ARRAY_BUFFER, nId );
	glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindVertexArray( 0 );

	vBuffered = false;
	tBuffered = false;
	nBuffered = false;
}

VertexBuffer::~VertexBuffer()
{
	GLuint Ids[ 3 ];
	Ids[ 0 ] = vId;
	Ids[ 1 ] = tId;
	Ids[ 2 ] = nId;
	glDeleteBuffers( 3, Ids );
	glDeleteVertexArrays( 1, &vao );
}

void VertexBuffer::buffer( unsigned long nVertices, void *vertices, void *texCoords, void *normals )
{
	if( vertices != NULL )
	{
		glBindBuffer( GL_ARRAY_BUFFER, vId );
		glBufferData( GL_ARRAY_BUFFER, nVertices * 3 * sizeof( GLfloat ), vertices, GL_STATIC_DRAW );
		vBuffered = true;
	}

	if( texCoords != NULL )
	{
		glBindBuffer( GL_ARRAY_BUFFER, tId );
		glBufferData( GL_ARRAY_BUFFER, nVertices * 2 * sizeof( GLfloat ), texCoords, GL_STATIC_DRAW );
		tBuffered = true;
	}

	if( normals != NULL )
	{
		glBindBuffer( GL_ARRAY_BUFFER, nId );
		glBufferData( GL_ARRAY_BUFFER, nVertices * 3 * sizeof( GLfloat ), normals, GL_STATIC_DRAW );
		nBuffered = true;
	}

	size = nVertices;
}

void VertexBuffer::draw( unsigned int primitive )
{
	if( primitive == 0 )
		primitive = GL_TRIANGLES;

	if( !vBuffered && !tBuffered && !nBuffered )
		assert( false );

	glBindVertexArray( vao );

	if( vBuffered )
	{
		glEnableVertexAttribArray( 0 );
	}

	if( tBuffered )
	{
		glEnableVertexAttribArray( 1 );
	}

	if( nBuffered )
	{
		glEnableVertexAttribArray( 2 );
	}

	glDrawArrays( primitive, 0, size );

	if( vBuffered )
		glDisableVertexAttribArray( 0 );
	if( tBuffered )
		glDisableVertexAttribArray( 1 );
	if( nBuffered )
		glDisableVertexAttribArray( 2 );

	glBindVertexArray( 0 );
}

