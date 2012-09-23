#ifndef TEXTURE_H
#define TEXTURE_H

#include "Image.h"

class Texture
{
public:
	Texture();
	virtual ~Texture();
	virtual void bind( unsigned int unit ){}
	unsigned int getId() const{ return Id; }

private:
	unsigned int Id;
};

#endif

