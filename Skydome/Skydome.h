#pragma once

#include "Model.h"
#include "MyFunc/MyFunc.h"
#include "WorldTransform.h"
#include <cassert>


/// <summary>
/// 天球
/// </summary>
class Skydome
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection viewProjection);

private:
	// ワールド返還データ
	WorldTransform worldTransform_;
	// 
	ViewProjection viewProjection_;
	// モデル
	Model* model_ = nullptr;
};