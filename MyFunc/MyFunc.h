#include "math.h"
#include "MathUtility.h"
#include "Matrix4.h"
#include "WorldTransform.h"

#pragma once
namespace MyFunc
{
	/// <summary>
	/// affine�ϊ��̌v�Z����
	/// </summary>
	/// <param name="worldTransform">����object�̏�Ԃ��擾</param>
	/// <param name="i">�e�q�֌W������ꍇfor���Ŋ֌W��������</param>
	void Matrix4(WorldTransform& worldTransform, int i);
};