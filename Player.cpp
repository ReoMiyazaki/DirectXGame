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
	// キャラクター移動の速さ
	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) { worldTransform_.translation_.x -= kCharacterSpeed; }
	else if (input_->PushKey(DIK_RIGHT)) { worldTransform_.translation_.x += kCharacterSpeed; }

	if (input_->PushKey(DIK_UP)) { worldTransform_.translation_.y += kCharacterSpeed; }
	else if (input_->PushKey(DIK_DOWN)) { worldTransform_.translation_.y -= kCharacterSpeed; }

	// 制限限界座標
	const float kMoveLimitX = 35.0f;
	const float kMoveLimitY = 19.0f;
	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
	// デバッグ用表示
	debugText_->SetPos(50, 150);
	debugText_->Printf(
		"Root:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
}

void Player::Attack()
{
	if (input_->PushKey(DIK_SPACE))
	{
		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);
		// 弾を登録する
		bullet_ = newBullet;
	}
}

void Player::Update()
{
	Move();
	Rotate();
	Attack();
	// 弾更新
	if (bullet_) { bullet_->Update(); }
	MyFunc::Transform(worldTransform_, 0);
}

void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	// 弾描画
	if (bullet_) { bullet_->Draw(viewProjection); }
}