#include "math.h"
#include "MathUtility.h"
#include "Matrix4.h"
#include "WorldTransform.h"

#pragma once
namespace MyFunc
{
	/// <summary>
	/// affine変換の計算処理
	/// </summary>
	/// <param name="worldTransform">そのobjectの状態を取得</param>
	/// <param name="i">親子関係がある場合for文で関係数分処理</param>
	void Matrix4(WorldTransform& worldTransform, int i);
};