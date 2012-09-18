#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>

class Vector3D
{
public:
	Vector3D( float x = 0.0f, float y = 0.0f, float z = 0.0f )
	{
		xyz[ 0 ] = x;
		xyz[ 1 ] = y;
		xyz[ 2 ] = z;
	}

	~Vector3D()
	{
	}

	float length() const
	{
		return sqrt( xyz[ 0 ] * xyz[ 0 ] + xyz[ 1 ] * xyz[ 1 ] + xyz[ 2 ] * xyz[ 2 ] );
	}

	void normalize()
	{
		float l = length();
		for( int i = 0; i < 3; i++ )
			xyz[ i ] /= l;
	}

	const float* getAsArray() const
	{
		return xyz;
	}

	void initFromArray( const float *a )
	{
		for( int i = 0; i < 3; i++ )
			xyz[ i ] = a[ i ];
	}

	void add( const Vector3D &other )
	{
		const float *f = other.getAsArray();
		for( int i = 0; i < 3; i++ )
			xyz[ i ] += f[ i ];
	}

	void sub( const Vector3D &other )
	{
		const float *f = other.getAsArray();
		for( int i = 0; i < 3; i ++ )
			xyz[ i ] -= f[ i ];
	}

	float dot( const Vector3D &other )
	{
		float result = 0.0f;
		const float *f = other.getAsArray();
		for( int i = 0; i < 3; i++ )
			result += ( xyz[ i ] * f[ i ] );
	}

private:
	float xyz[ 3 ];
};

#endif

