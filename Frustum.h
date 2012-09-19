#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <cmath>

class Frustum
{
public:
	Frustum()
	{
		loadIdentity();
	}

	~Frustum()
	{
	}

	void loadAllZero()
	{
		for( int i = 0; i < 16; i++ )
			m[ i ] = 0.0f;
	}

	void loadIdentity()
	{
		loadAllZero();

		m[ 0 ]  = 1.0f;
		m[ 5 ]  = 1.0f;
		m[ 10 ] = 1.0f;
		m[ 15 ] = 1.0f;
	}

	void ortho( float left, float right, float bottom, float top, float near, float far )
	{
		loadAllZero();
		m[ 0 ]  = 2.0f / ( right - left );
		m[ 5 ]  = 2.0f / ( top - bottom );
		m[ 10 ] = -1.0f * 2.0f / ( far - near );
		m[ 12 ] = -1.0f * ( right + left ) / ( right - left );
		m[ 13 ] = -1.0f * ( top + bottom ) / ( top - bottom );
		m[ 14 ] = -1.0f * ( far + near ) / ( far - near );
		m[ 15 ] = 1.0f;
	}

	void ortho2D( float left, float right, float bottom, float top )
	{
		ortho( left, right, bottom, top, -1.0f, 1.0f );
	}

	void perspective( float fov, float aspect, float near, float far )
	{
		float f = 1.0f / tan( fov / 2.0f );
		float m[ 16 ];
		m[ 0 ] = f / aspect;
		m[ 1 ] = 0.0f;
		m[ 2 ] = 0.0f;
		m[ 3 ] = 0.0f;

		m[ 4 ] = 0.0f;
		m[ 5 ] = f;
		m[ 6 ] = 0.0f;
		m[ 7 ] = 0.0f;

		m[ 8 ] = 0.0f;
		m[ 9 ] = 0.0f;
		m[ 10 ] = ( far + near ) / ( near - far );
		m[ 11 ] = -1.0f;

		m[ 12 ] = 0.0f;
		m[ 13 ] = 0.0f;
		m[ 14 ] = 2*far*near / ( near - far );
		m[ 15 ] = 0.0f;
	}

	const float* getAsArray() const
	{
		return m;
	}

private:
	float m[ 16 ];
};

#endif

