#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <gl/glew.h>
#include <gl/gl.h>
#include <cassert>
#include "CubeMapTexture.h"

void CubeMapTexture::bind( unsigned int unit )
{
	glActiveTexture( GL_TEXTURE0 + unit );
	glBindTexture( GL_TEXTURE_CUBE_MAP, getId() );
}

void CubeMapTexture::loadImage( TexturePart part, Image &image )
{
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	unsigned char depth = image.getDepth() / 8;
	unsigned short format;
	unsigned short components;

	switch( depth )
	{
	case 1:
		format = GL_LUMINANCE;
		components = GL_LUMINANCE;
		break;

	case 3:
		format = GL_BGR;
		components = GL_RGB;
		break;

	case 4:
		format = GL_BGRA;
		components = GL_RGBA;
		break;

	default:
		assert( false );
		break;
	}
	
	glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + part,
														0,
														components,
														image.getWidth(),
														image.getHeight(),
														0,
														format,
														GL_UNSIGNED_BYTE,
														image.getBuffer() );

}

void CubeMapTexture::loadImage( Image &image )
{
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	unsigned char depth = image.getDepth() / 8;
	unsigned short format;
	unsigned short components;

	switch( depth )
	{
	case 1:
		format = GL_LUMINANCE;
		components = GL_LUMINANCE;
		break;

	case 3:
		format = GL_BGR;
		components = GL_RGB;
		break;

	case 4:
		format = GL_BGRA;
		components = GL_RGBA;
		break;

	default:
		assert( false );
		break;
	}
	
	for( unsigned int i = POS_X_PART; i <= NEG_Z_PART; i++ )
		glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
														0,
														components,
														image.getWidth(),
														image.getHeight(),
														0,
														format,
														GL_UNSIGNED_BYTE,
														image.getBuffer() );


}
