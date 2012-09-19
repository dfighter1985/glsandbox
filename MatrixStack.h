#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include "Matrix44.h"
#include <cmath>
#include <stack>

class MatrixStack
{
public:
	MatrixStack()
	{
		Matrix44 m;
		stack.push( m );
	}

	~MatrixStack()
	{
	}

	void push()
	{
		stack.push( stack.top() );
	}

	void pop()
	{
		stack.pop();
	}

	const Matrix44& top() const
	{
		return stack.top();
	}

	const unsigned long size() const
	{
		return stack.size();
	}

	void loadIdentity()
	{
		stack.top().loadIdentity();
	}

	void translate( float x, float y, float z )
	{
		float xyzw[ 4 ];
		xyzw[ 0 ] = x;
		xyzw[ 1 ] = y;
		xyzw[ 2 ] = z;
		xyzw[ 3 ] = 1.0f;

		Matrix44 m;
		m.loadIdentity();
		m.setColumn( 3, xyzw );

		stack.top().mul( m );
	}

	void scale( float x, float y, float z )
	{
		float f[ 16 ];
		for( int i = 0; i < 16; i++ )
			f[ i ] = 0.0f;
		
		f[ 0 ]  = x;
		f[ 5 ]  = y;
		f[ 10 ] = z;
		f[ 15 ] = 1.0f;

		Matrix44 m;
		m.initFromArray( f );
		stack.top().mul( m );
	}

	void rotate( float angle, float x, float y, float z )
	{
		float l = sqrt( x*x + y*y + z*z );
		if( ( l > 1.01f ) || ( l < 0.99f ) )
		{
			x /= l;
			y /= l;
			z /= l;
		}

		float angleRad = angle * 3.14159f / 180.0f;
		float c = cosf( angleRad );
		float s = sinf( angleRad );
		float mc = 1 - c;

		float ma[ 16 ];
		ma[ 0 ]  = x * x * mc + c;
		ma[ 1 ]  = y * x * mc + z * s;
		ma[ 2 ]  = x * z * mc - y * s;
		ma[ 3 ]  = 0.0f;

		ma[ 4 ]  = x * y * mc - z * s;
		ma[ 5 ]  = y * y * mc + c;
		ma[ 6 ]  = y * z * mc + x * s;
		ma[ 7 ]  = 0.0f;

		ma[ 8 ]  = x * z * mc + y * s;
		ma[ 9 ]  = y * z * mc - x * s;
		ma[ 10 ] = z * z * mc + c;
		ma[ 11 ] = 0.0f;

		ma[ 12 ] = 0.0f;
		ma[ 13 ] = 0.0f;
		ma[ 14 ] = 0.0f;
		ma[ 15 ] = 1.0f;

		Matrix44 m;
		m.initFromArray( ma );
		stack.top().mul( m );
	}

private:
	std::stack< Matrix44 > stack;
};

#endif

