#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>

class Vector3
{
public:
	Vector3( float x = 0.0f, float y = 0.0f, float z = 0.0f )
	{
		xyz[ 0 ] = x;
		xyz[ 1 ] = y;
		xyz[ 2 ] = z;
	}

	~Vector3()
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

	void add( const Vector3 &other )
	{
		const float *f = other.getAsArray();
		for( int i = 0; i < 3; i++ )
			xyz[ i ] += f[ i ];
	}

	void sub( const Vector3 &other )
	{
		const float *f = other.getAsArray();
		for( int i = 0; i < 3; i ++ )
			xyz[ i ] -= f[ i ];
	}

	void mul( float scalar )
	{
		for( int i = 0; i < 3; i++ )
			xyz[ i ] *= scalar;
	}

	float dot( const Vector3 &other )
	{
		float result = 0.0f;
		const float *f = other.getAsArray();
		for( int i = 0; i < 3; i++ )
			result += ( xyz[ i ] * f[ i ] );
		
		return result;
	}

	// Vector cross product A x B
	// this vector is B
	// other is A
	Vector3 cross( const Vector3 &other )
	{
		const float *A = other.getAsArray();
		const float *B = getAsArray();

		float i = A[ 1 ] * B[ 2 ] - B[ 1 ] * A[ 2 ];
		float j = A[ 0 ] * B[ 2 ] - B[ 0 ] * A[ 2 ];
		float k = A[ 0 ] * B[ 1 ] - B[ 0 ] * A[ 1 ];

		return Vector3( i, j, k );
	}

private:
	float xyz[ 3 ];
};

#endif

