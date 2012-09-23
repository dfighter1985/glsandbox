#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <gl/glew.h>
#include <gl/gl.h>
#include <cassert>
#include "Texture.h"

Texture::Texture()
{
	Id = 0;
	glGenTextures( 1, &Id );
}

Texture::~Texture()
{
	glDeleteTextures( 1, &Id );
	Id = 0;
}

