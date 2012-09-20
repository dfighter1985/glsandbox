#include "TGAFile.h"
#include <fstream>


TGAFile::TGAFile()
{
	image = NULL;
}

TGAFile::~TGAFile()
{
	clear();
}

bool TGAFile::load( const std::string &fileName )
{
	f.open( fileName.c_str(), std::fstream::in | std::fstream::binary );
	if( !f.good() )
		return false;

	if( !readHeader() )
	{
		f.close();
		return false;
	}

	if( header.identSize > 0 )
	{
		if( !readIdent() )
		{
			f.close();
			return false;
		}
	}

	if( header.colorMapLength > 0 )
	{
		if( !readPalette() )
		{
			f.close();
			return false;
		}
	}

	if( !readImage() )
	{
		f.close();
		return false;
	}

	f.close();
	return true;
}

void TGAFile::clear()
{
	if( f.is_open() )
		f.close();
	delete image;
	image = NULL;
}

bool TGAFile::readHeader()
{
	f.read( (char*)&header.identSize, sizeof( header.identSize ) );
	f.read( (char*)&header.colorMapType, sizeof( header.colorMapType ) );
	f.read( (char*)&header.imageType, sizeof( header.imageType ) );
	f.read( (char*)&header.colorMapStart, sizeof( header.colorMapStart ) );
	f.read( (char*)&header.colorMapLength, sizeof( header.colorMapLength ) );
	f.read( (char*)&header.colorMapBits, sizeof( header.colorMapBits ) );
	f.read( (char*)&header.x, sizeof( header.x ) );
	f.read( (char*)&header.y, sizeof( header.y ) );
	f.read( (char*)&header.width, sizeof( header.width ) );
	f.read( (char*)&header.height, sizeof( header.height ) );
	f.read( (char*)&header.bitsPerPixel, sizeof( header.bitsPerPixel ) );
	f.read( (char*)&header.descriptor, sizeof( header.descriptor ) );

	if( f.good() )
		return true;
	else
		return false;
}

bool TGAFile::readIdent()
{
	char ident[ sizeof( short ) ];
	f.read( ident, header.identSize );

	if( f.good() )
		return true;
	else
		return false;
}

bool TGAFile::readPalette()
{
	// Palettes aren't supported for now
	return false;
}

bool TGAFile::readImage()
{
	unsigned char bytesPerPixel = header.bitsPerPixel / 8;
	unsigned long len = bytesPerPixel * header.height * header.width;

	if( image != NULL )
		delete image;
	image = new Image( header.height, header.width, header.bitsPerPixel );
	image->createBuffer();
	f.read( (char*)image->getBuffer(), len );

	if( f.good() )
		return true;
	else
	{
		delete image;
		image = NULL;
		return false;
	}
}

