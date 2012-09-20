#ifndef IMAGE_H
#define IMAGE_H

class Image
{
public:
	Image( unsigned int height, unsigned int width, unsigned char depth )
	{
		this->height = height;
		this->width  = width;
		this->depth  = depth;
		buffer       = NULL;
	}

	~Image()
	{
		delete[] buffer;
		buffer = NULL;
	}

	void createBuffer()
	{
		if( buffer != NULL )
			delete[] buffer;
		buffer = new char[ width * height * depth / 8 ];
	}

	void* getBuffer()
	{
		return buffer;
	}

	unsigned int getHeight() const
	{
		return height;
	}

	unsigned int getWidth() const
	{
		return width;
	}

	unsigned char getDepth()
	{
		return depth;
	}

private:
	unsigned int height;
	unsigned int width;
	unsigned char depth;
	char *buffer;
};

#endif

