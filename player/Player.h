#pragma once

#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "func/MyFunc.h"
#include "PlayerBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "math.h"
#include <cassert>
#include <memory>
#include <list>

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
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

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
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

};

