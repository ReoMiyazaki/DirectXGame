#pragma once

#include "Model.h"
#include "MyFunc.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>

class Enemy
{

public:
	void Initialize(Model* model, uint32_t textureHandle);
	void UpDate();
	void Draw(ViewProjection viewProjection);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

};