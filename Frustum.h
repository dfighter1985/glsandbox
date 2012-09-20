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

	void ortho( float left, float right, float bottom, float top, float zNear, float zFar )
	{
		loadAllZero();
		m[ 0 ]  = 2.0f / ( right - left );
		m[ 5 ]  = 2.0f / ( top - bottom );
		m[ 10 ] = -1.0f * 2.0f / ( zFar - zNear );
		m[ 12 ] = -1.0f * ( right + left ) / ( right - left );
		m[ 13 ] = -1.0f * ( top + bottom ) / ( top - bottom );
		m[ 14 ] = -1.0f * ( zFar + zNear ) / ( zFar - zNear );
		m[ 15 ] = 1.0f;
	}

	void ortho2D( float left, float right, float bottom, float top )
	{
		ortho( left, right, bottom, top, -1.0f, 1.0f );
	}

	void perspective( float fov, float aspect, float zNear, float zFar )
	{
		float f = 1.0f / tan( fov / 2.0f );

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
		m[ 10 ] = ( zFar + zNear ) / ( zNear - zFar );
		m[ 11 ] = -1.0f;

		m[ 12 ] = 0.0f;
		m[ 13 ] = 0.0f;
		m[ 14 ] = 2 * zFar * zNear / ( zNear - zFar );
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

