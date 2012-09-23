#ifndef CMTEXTURE_H
#define CMTEXTURE_H

#include "Texture.h"

class CubeMapTexture : public Texture
{
public:

	enum TexturePart
	{
		POS_X_PART,
		NEG_X_PART,
		POS_Y_PART,
		NEG_Y_PART,
		POS_Z_PART,
		NEG_Z_PART
	};

	CubeMapTexture(){}
	~CubeMapTexture(){}
	void bind( unsigned int unit );
	void loadImage( TexturePart part, Image &image );
	void loadImage( Image &image );

private:
};

#endif

