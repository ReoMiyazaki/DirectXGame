#pragma once

#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyFunc.h"
#include "PlayerBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
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

	void Rotate();	// 旋回
	void Move();	// 移動
	void Attack();	// 攻撃

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection viewPojection);

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

	// 弾
	PlayerBullet* bullet_ = nullptr;

};

