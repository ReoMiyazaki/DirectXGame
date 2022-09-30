#pragma once

#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyFunc/MyFunc.h"
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

	// 旋回
	void Rotate();
	// 移動
	void Move();
	// 攻撃
	void Attack();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection viewPojection);

	Vector3 RotationOperator(Vector3& velocity, WorldTransform& worldTransform);
	// ワールド座標を取得
	Vector3 GetWorldPosition();

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	//タマリストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& GetBulletd() { return bullets_; }

	void DeleteBullet();

	Matrix4 GetMatrix();

	int hp = 10;


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

	//打ち出すまでの時間
	float coolTimer = 0.0f;

};

