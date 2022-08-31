#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{

	// 乱数シード生成器
//	std::random_device seed_gen;
	// メルセンヌ・ツイスターの乱数エンジン
//	std::mt19937_64 engin(seed_gen());
	// 乱数範囲の指定
//	std::uniform_real_distribution<float> trans(-10, 10);

	// NULLポインタチェック
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記録する
	this->model_ = model;
	this->textureHandle_ = textureHandle;
	// ワールド変換の初期化
	worldTransform_.Initialize();
//	worldTransform_.translation_ = { trans(engin), trans(engin), trans(engin) };
}
void Enemy::UpDate()
{
	MyFunc::Matrix4(worldTransform_, 0);
}

void Enemy::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
