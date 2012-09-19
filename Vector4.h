#ifndef VECTOR4_H
#define VECTOR4_H

#include <cmath>

class Vector4
{
public:
	Vector4( float x = 0.0f, float y = 0.0f, float z = 0.0f  )
	{
		xyzw[ 0 ] = x;
		xyzw[ 1 ] = y;
		xyzw[ 2 ] = z;
		xyzw[ 3 ] = 1.0f;
	}

	~Vector4()
	{
	}

	float length() const
	{
		return sqrt( xyzw[ 0 ] * xyzw[ 0 ] + xyzw[ 1 ] * xyzw[ 1 ] + xyzw[ 2 ] * xyzw[ 2 ] );
	}

	void normalize()
	{
		float l = length();
		for( int i = 0; i < 3; i++ )
			xyzw[ i ] /= l;
	}

	const float* getAsArray() const
	{
		return xyzw;
	}

	void initFromArray( const float *a )
	{
		for( int i = 0; i < 3; i++ )
			xyzw[ i ] = a[ i ];
		xyzw[ 3 ] = 1.0f;
	}

	void add( const Vector4 &other )
	{
		const float *f = other.getAsArray();
		for( int i = 0; i < 3; i++ )
			xyzw[ i ] += f[ i ];
	}

	void sub( const Vector4 &other )
	{
		const float *f = other.getAsArray();
		for( int i = 0; i < 3; i++ )
			xyzw[ i ] -= f[ i ];
	}

	void mul( float scalar )
	{
		for( int i = 0; i < 3; i++ )
			xyzw[ i ] *= scalar;
	}

	float dot( const Vector4 &other )
	{
		float result = 0.0f;
		const float *f = other.getAsArray();
		for( int i = 0; i < 3; i++ )
			result += ( xyzw[ i ]  * f[ i ] );

		return result;
	}

	// Vector cross product A x B
	// this vector is B
	// other is A
	Vector4 cross( const Vector4 &other )
	{
		const float *A = other.getAsArray();
		const float *B = getAsArray();

		float i = A[ 1 ] * B[ 2 ] - B[ 1 ] * A[ 2 ];
		float j = A[ 0 ] * B[ 2 ] - B[ 0 ] * A[ 2 ];
		float k = A[ 0 ] * B[ 1 ] - B[ 0 ] * A[ 1 ];

		return Vector4( i, j, k );
	}

private:
	float xyzw[ 4 ];
};

#endif
