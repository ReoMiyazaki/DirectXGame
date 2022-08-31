#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position)
{
	// NULLポインタ
	assert(model);
	model_ = model;
	// テクスチャハンドル読み込み
	textureHandle_ = TextureManager::Load("black.png");
	worldTransform_.Initialize();
	// 引数で受け取った初期化座標をリセット
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update()
{
	MyFunc::Transform(worldTransform_, 0);
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
