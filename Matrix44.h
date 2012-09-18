#ifndef MATRIX44_H
#define MATRIX44_H

#include <cmath>

class Matrix44
{
public:
	Matrix44()
	{
		loadAllZero();
	}

	~Matrix44()
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
		for( int i = 0; i <= 3; i++ )
			m[ i*5 ] = 1.0f;
	}

	const float* getAsArray() const
	{
		return m;
	}

	void initFromArray( const float *a )
	{
		for( int i = 0; i < 16; i++ )
			m[ i ] = a[ i ];
	}

	void assign( const Matrix44& other )
	{
		initFromArray( other.getAsArray() );
	}

	void add( const Matrix44& other )
	{
		const float *f = other.getAsArray();
		for( int i = 0; i < 16; i++ )
			m[ i ] += f[ i ];
	}

	void sub( const Matrix44& other )
	{
		const float *f = other.getAsArray();
		for( int i = 0; i < 16; i++ )
			m[ i ] -= f[ i ];
	}

	void mul( float scalar )
	{
		for( int i = 0; i < 16; i++ )
			m[ i ] *= scalar;
	}

	// A*B=C
	// This matrix is B
	// other is A
	// result is C, which is loaded back into B
	void mul( const Matrix44 &other )
	{
		const float *A = other.getAsArray();
		const float *B = getAsArray();
		float C[ 16 ];
		int l = 0;

		for( int i = 0; i < 4; i++ ) // column of B
			for( int j = 0; j < 4; j++ ) // row of A
			{
				C[ l ] = 0.0f;

				for( int k = 0; k < 4; k++ ) // column of A, row of B
					C[ l ] += ( A[ j + k*4 ] * B[ i*4 + k ] );

				l++; // field of C
			}


		initFromArray( C );
	}

private:
	float m[ 16 ];
};

#endif

