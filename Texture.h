#ifndef TEXTURE_H
#define TEXTURE_H

#include "Image.h"

class Texture
{
public:
	Texture();
	~Texture();
	void bind( unsigned int unit );
	void loadImage( Image &image );
	unsigned int getId() const{ return Id; }

private:
	unsigned int Id;
};

#endif

