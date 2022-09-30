#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle)
{
	// NULLポインタチェック
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記録する
	this->model_ = model;
	this->textureHandle_ = textureHandle;
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Player::Rotate()
{
	const float kRotateSpd = 0.02f;

	if (input_->PushKey(DIK_D)) { worldTransform_.rotation_.y -= kRotateSpd; }
	else if (input_->PushKey(DIK_A)) { worldTransform_.rotation_.y += kRotateSpd; }
}

void Player::Move()
{
	// キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };
	// キャラクター移動の速さ
	const float kCharacterSpeed = 0.2f;
	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_LEFT)) { move.x = -kCharacterSpeed; }
	else if (input_->PushKey(DIK_RIGHT)) { move.x = kCharacterSpeed; }

	if (input_->PushKey(DIK_UP)) { move.y = kCharacterSpeed; }
	else if (input_->PushKey(DIK_DOWN)) { move.y = -kCharacterSpeed; }

	worldTransform_.translation_ += move;
	// 制限限界座標
	const float kMoveLimitX = 35.0f;
	const float kMoveLimitY = 19.0f;
	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
	MyFunc::Matrix4(worldTransform_, 0);
	// デバッグ用表示
	debugText_->SetPos(50, 150);
	debugText_->Printf(
		"Root:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
}

void Player::Attack()
{
	if (input_->TriggerKey(DIK_SPACE))
	{
		// 自キャラの座標をコピー
		Vector3 position = worldTransform_.translation_;
		// 弾の速度 
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		velocity = RotationOperator(velocity, worldTransform_);
		// 弾を生成し、初期化
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, position, velocity);
		// 弾を登録する
		bullets_.push_back(std::move(newBullet));
	}
}

void Player::OnCollision() {}



void Player::Update()
{
	Rotate();
	Move();
	Attack();
	DeleteBullet();

	// 弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) { bullet->Update(); }

	// ですフラグの立った弾を削除
//	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {return bullet->IsDead(); });
}

void Player::DeleteBullet()
{
	// デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {return bullet->IsDead(); });
}


void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	// 弾描画
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) { bullet->Draw(viewProjection); }
}

Vector3 Player::RotationOperator(Vector3& velocity, WorldTransform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//内積
	result.z = velocity.x * worldTransform.matWorld_.m[0][2] +
		velocity.y * worldTransform.matWorld_.m[1][2] +
		velocity.z * worldTransform.matWorld_.m[2][2];

	result.x = velocity.x * worldTransform.matWorld_.m[0][0] +
		velocity.y * worldTransform.matWorld_.m[1][0] +
		velocity.z * worldTransform.matWorld_.m[2][0];

	result.y = velocity.x * worldTransform.matWorld_.m[0][1] +
		velocity.y * worldTransform.matWorld_.m[1][1] +
		velocity.z * worldTransform.matWorld_.m[2][1];

	return result;
}

Vector3 Player::GetWorldPosition()
{
	//ワールド座標を入れるための変数
	Vector3 worldPos;

	//ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
