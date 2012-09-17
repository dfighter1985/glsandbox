#ifndef TGAFILE_H
#define TGAFILE_H

#include <fstream>
#include <string>

class TGAFile
{
private:

	struct TGAHeader
	{
		unsigned char identSize;
		unsigned char colorMapType;
		unsigned char imageType;
		unsigned short colorMapStart;
		unsigned short colorMapLength;
		unsigned char colorMapBits;
		unsigned short x;
		unsigned short y;
		unsigned short width;
		unsigned short height;
		unsigned char bitsPerPixel;
		unsigned char descriptor;
	}header;

public:
	TGAFile();
	~TGAFile();

	unsigned short getWidth() const{ return header.width; }
	unsigned short getHeight() const{ return header.height; }
	unsigned short getDepth() const{ return header.bitsPerPixel / 8; }
	const void* getBuffer() const{ return buffer; }

	bool load( const std::string &fileName );
	void clear();

private:
	bool readHeader();
	bool readIdent();
	bool readPalette();
	bool readImage();

	std::ifstream f;
	void* buffer;
};


#endif
