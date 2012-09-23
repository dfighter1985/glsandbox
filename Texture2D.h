#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "Texture.h"

class Texture2D : public Texture
{
public:
	Texture2D(){}
	~Texture2D(){}
	void bind( unsigned int unit );
	void loadImage( Image &image );

private:

};

#endif
