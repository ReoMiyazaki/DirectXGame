#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{

	// 乱数シード生成器
	std::random_device seed_gen;
	// メルセンヌ・ツイスターの乱数エンジン
	std::mt19937_64 engin(seed_gen());
	// 乱数範囲の指定
	std::uniform_real_distribution<float> trans(-10, 10);

	// NULLポインタチェック
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記録する
	this->model_ = model;
	this->textureHandle_ = textureHandle;
	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = { trans(engin), trans(engin), 50 };
}

void Enemy::Approach()
{
	//接近速度
	Vector3 approach_ = { 0.0f, 0.0f, -0.1f };

	worldTransform_.translation_ += approach_;
	//既定の位置に到達したら離脱
	if (worldTransform_.translation_.z <= 0.0f)
	{
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave()
{
	//離脱速度
	Vector3 leave_ = { -0.15f,0.1f,0.1f };

	worldTransform_.translation_ += leave_;
}

void Enemy::UpDate()
{
	MyFunc::Matrix4(worldTransform_, 0);
	switch (phase_) {
	case Phase::Approach://接近フェーズ
	default:
		//移動
		Approach();
		break;

	case Phase::Leave://離脱フェーズ
		Leave();
		break;
	}
}

void Enemy::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
