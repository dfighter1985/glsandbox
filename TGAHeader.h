#ifndef TGAHEADER_H
#define TGAHEADER_H

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
};

#endif
