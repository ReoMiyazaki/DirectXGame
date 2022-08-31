#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	// NULLポインタ
	assert(model);
	model_ = model;
	velocity_ = velocity;
	// テクスチャハンドル読み込み
	textureHandle_ = TextureManager::Load("black.png");
	worldTransform_.Initialize();
	// 引数で受け取った初期化座標をリセット
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update()
{
	// 座標を移動させる
	worldTransform_.translation_ += velocity_;
	MyFunc::Matrix4(worldTransform_, 0);
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
