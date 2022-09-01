#pragma once

#include "EnemyBullet.h"
#include "Model.h"
#include "MyFunc/MyFunc.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>

// 自機クラスの前方宣言
class Player;

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
	// 弾発射
	void Fire();
	// 更新
	void UpDate();
	// 描画
	void Draw(ViewProjection viewProjection);

	void SetPlayer(Player* player) { player_ = player; }

	// ワールド座標を取得
	Vector3 GetWorldPosition();
  
	void OnCollision();

	//弾リスト
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }

	void DeleteBullet();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//敵の行動パターン
	Phase phase_ = Phase::None;

	// 弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	//打ち出すまでの時間
	float coolTimer = 0.0f;

	// 自キャラ
	Player* player_ = nullptr;
};