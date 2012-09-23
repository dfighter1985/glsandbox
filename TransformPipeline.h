#ifndef TRANSFORMPIPELINE_H
#define TRANSFORMPIPELINE_H

#include "MatrixStack.h"
#include "Frustum.h"

class TransformPipeline
{
public:
	TransformPipeline()
	{
	}

	~TransformPipeline()
	{
	}

	void setup( MatrixStack *modelView, Frustum *frustum )
	{
		mv = modelView;
		p  = frustum;
	}

	const float* getModelViewMatrix() const
	{
		return mv->top().getAsArray();
	}

	const float* getProjectionMatrix() const
	{
		return p->getAsArray();
	}

	const float* getMVPMatrix()
	{
		m.assign( mv->top() );
		m.mul( p->getAsArray() );
		return m.getAsArray();
	}

	const float* getNormalMatrix()
	{
		normalMatrix.loadIdentity();
		float v[ 4 ];

		for( int i = 0; i < 3; i++ )
		{
			mv->top().getColumn( i, v );
			normalMatrix.setColumn( i, v );
		}
		return normalMatrix.getAsArray();
	}

private:
	MatrixStack *mv;
	Frustum  *p;
	Matrix44  m;
	Matrix44  normalMatrix;
};

#endif
