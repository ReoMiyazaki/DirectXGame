#pragma once

#include "Model.h"
#include "MyFunc/MyFunc.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>

class Enemy
{
	enum class Phase
	{
		None,
		Approach,	//接近する
		Leave,		//離脱する
	};

public:
	// 初期化
	void Initialize(Model* model, uint32_t textureHandle);
	// 接近
	void Approach();
	// 離脱
	void Leave();
	// 更新
	void UpDate();
	// 描画
	void Draw(ViewProjection viewProjection);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//敵の行動パターン
	Phase phase_ = Phase::None;

};