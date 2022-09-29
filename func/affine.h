#include "math.h"
#include "MathUtility.h"
#include "Matrix4.h"
#include "WorldTransform.h"

#pragma once
namespace affine
{
	enum AXIS_NUM
	{
		AXIS_NONE,	// 0
		AXIS_X,		// 1
		AXIS_Y,		// 2
		AXIS_XY,	// 3
		AXIS_Z,		// 4
		AXIS_XZ,	// 5
		AXIS_YZ,	// 6
		AXIS_XYZ,	// 7
	};

	typedef struct AffineMat
	{
		Matrix4 scale = MathUtility::Matrix4Identity();
		Matrix4 rotX = MathUtility::Matrix4Identity();
		Matrix4 rotY = MathUtility::Matrix4Identity();
		Matrix4 rotZ = MathUtility::Matrix4Identity();
		Matrix4 transform = MathUtility::Matrix4Identity();
	};

	void setScaleMat(Matrix4& mat, WorldTransform& worldTransform);
	void setRotateMat(AffineMat& mat, WorldTransform& worldTransform);
	void setTransformMat(Matrix4& mat, WorldTransform& worldTransform);

	Matrix4 generatScaleMat(WorldTransform& worldTransform);
	Matrix4 generatRotateXMat(WorldTransform& worldTransform);
	Matrix4 generatRotateYMat(WorldTransform& worldTransform);
	Matrix4 generatRotateZMat(WorldTransform& worldTransform);
	Matrix4 generatTransformMat(WorldTransform& worldTransform);

	void setTransformationWorldMat(AffineMat& affineMat, WorldTransform& worldTransform);
};

