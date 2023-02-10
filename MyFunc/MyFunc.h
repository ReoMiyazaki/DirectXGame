#include "math.h"
#include "MathUtility.h"
#include "Matrix4.h"
#include "WorldTransform.h"

#pragma once
namespace MyFunc
{
	/// <summary>
	/// affine•ÏŠ·‚ÌŒvZˆ—
	/// </summary>
	/// <param name="worldTransform">‚»‚Ìobject‚Ìó‘Ô‚ğæ“¾</param>
	/// <param name="i">eqŠÖŒW‚ª‚ ‚éê‡for•¶‚ÅŠÖŒW”•ªˆ—</param>
	void Matrix4(WorldTransform& worldTransform, int i);
};