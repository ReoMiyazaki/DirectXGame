#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	// NULLポインタ
	assert(model);
	model_ = model;
	velocity_ = velocity;
	// テクスチャハンドル読み込み
	textureHandle_ = TextureManager::Load("blue.png");
	worldTransform_.Initialize();
	// 引数で受け取った初期化座標をリセット
	worldTransform_.translation_ = position;
}

void EnemyBullet::Update()
{
	// 座標を移動させる
	worldTransform_.translation_ += velocity_;
	MyFunc::Matrix4(worldTransform_, 0);
	// 時間経過でデス
	if (--deathTimer_ <= 0) { isDead_ = true; }
}

void EnemyBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void EnemyBullet::OnCollision()
{
	isDead_ = true;
}

Vector3 EnemyBullet::GetWorldPosition()
{
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得
	worldPos = worldTransform_.translation_;
	return worldPos;
}

Matrix4 EnemyBullet::GetMatrix()
{
	return worldTransform_.matWorld_;
}