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

void Player::Update()
{
	Move();
	Attack();
	// 弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) { bullet->Update(); }
}

void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	// 弾描画
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) { bullet->Draw(viewProjection); }
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
	MyFunc::Transform(worldTransform_, 0);
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
		// 弾を生成し、初期化
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, position);
		// 弾を登録する
		bullets_.push_back(std::move(newBullet));
	}
}