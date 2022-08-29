#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"
#include "MyFunc.h"
#include "ViewProjection.h"
#include "math.h"
#include <cassert>

class Player
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name = "model" > モデル </param>
	/// <param name = "textureHamdle" > テクスチャハンドル </param>
	void Initialize(Model* model, uint32_t textureHandle);
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection viewPojection_);

private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	// ビュープロダクション
	ViewProjection viewProjection_;
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

};

