#ifndef MATH3D_H
#define MATH3D_H

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"
#include "MatrixStack.h"

inline Vector4 toVector4( const Vector3 &v )
{
	const float *f = v.getAsArray();
	return Vector4( f[ 0 ], f[ 1 ], f[ 2 ] );
}

inline Vector4 mulMatrix44Vector4( const Matrix44 &m, const Vector4 &v )
{
	const float *A = m.getAsArray();
	const float *B = v.getAsArray();
	float xyzw[ 4 ];

	for( int i = 0; i < 4; i++ )
	{
		xyzw[ i ] = 0.0f;

		for( int j = 0; j < 4; j++ )
			xyzw[ i ] += ( A[ i + j*4 ] * B[ j ] );
	}

	for( int i = 0; i < 3; i++ )
		xyzw[ i ] /= xyzw[ 3 ];
	xyzw[ 3 ] = 1.0f;

	return Vector4( xyzw[ 0 ], xyzw[ 1 ], xyzw[ 2 ] );
}

const float PI = 3.14159f;

inline float toRadian( float angle )
{
	return PI / 180.0f * angle;
}

inline float toAngle( float radian )
{
	return radian * 180.0f / PI;
}

#endif
