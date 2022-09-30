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

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	//タマリストを取得
	const std::list<std::unique_ptr<EnemyBullet>>& GetBulletd() { return bullets_; }

	void DeleteBullet();

	Matrix4 GetMatrix();

	int hp = 100;


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

	float dalayTimer = 0.0f;

	float x = 0.05f, y = 0.7f, z = 0.1f;

	// 自キャラ

	Player* player_ = nullptr;

	bool isDead_ = true;

};