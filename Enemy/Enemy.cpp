#include "Enemy.h"
#include "Player/Player.h"

using namespace MathUtility;

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
	DeleteBullet();
	Fire();
	// 弾更新
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) { bullet->Update(); }

	// ですフラグの立った弾を削除
//	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {return bullet->IsDead(); });
}

void Enemy::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	//弾描画
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) { bullet->Draw(viewProjection); }
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

void Enemy::Fire()
{
	dalayTimer -= 0.1f;

	// 弾の速度
	const float kBulletSpeed = 1.0f;


	assert(player_);

	Vector3 distance(0, 0, 0);


	//プレイヤーのワールド座標の取得
	Vector3 playerPosition = player_->GetWorldPosition();
	//敵のワールド座標の取得
	Vector3 enemyPosition = GetWorldPosition();

	//差分ベクトルを求める
	distance = playerPosition - enemyPosition;

	//長さを求める
	Vector3Length(distance);
	//正規化
	Vector3Normalize(distance);
	//ベクトルの長さを,速さに合わせる
	distance *= kBulletSpeed;	//これが速度になる

	if (dalayTimer <= 0) {

		// 弾を生成し、初期化
		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(model_, worldTransform_.translation_, distance);
		// 弾を登録する
		bullets_.push_back(std::move(newBullet));
		dalayTimer = 25.0f;
	}
}

void Enemy::OnCollision() {}

void Enemy::DeleteBullet()
{
	// デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {return bullet->IsDead(); });
}

Vector3 Enemy::GetWorldPosition()
{
	//ワールド座標を入れるための変数
	Vector3 worldPos;

	//ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Matrix4 Enemy::GetMatrix()
{
	return worldTransform_.matWorld_;
}