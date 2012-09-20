#ifndef TGAFILE_H
#define TGAFILE_H

#include <fstream>
#include <string>
#include "Image.h"
#include "TGAHeader.h"

class TGAFile
{
public:
	TGAFile();
	~TGAFile();

	unsigned short getWidth() const{ return header.width; }
	unsigned short getHeight() const{ return header.height; }
	unsigned short getDepth() const{ return header.bitsPerPixel / 8; }
	

	bool load( const std::string &fileName );
	void clear();
	Image* getImage() const{ return image; }

private:
	bool readHeader();
	bool readIdent();
	bool readPalette();
	bool readImage();

	std::ifstream f;
	TGAHeader header;
	Image *image;
};


#endif
