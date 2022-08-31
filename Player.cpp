#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);
	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	this->model_ = model;
	this->textureHandle_ = textureHandle;
	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	// ���[���h�ϊ��̏�����
	worldTransform_.Initialize();
}

void Player::Update()
{
	Move();
	Attack();
	// �e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) { bullet->Update(); }
}

void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	// �e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) { bullet->Draw(viewProjection); }
}

void Player::Move()
{
	// �L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };
	// �L�����N�^�[�ړ��̑���
	const float kCharacterSpeed = 0.2f;
	// �����������ňړ��x�N�g����ύX
	if (input_->PushKey(DIK_LEFT)) { move.x = -kCharacterSpeed; }
	else if (input_->PushKey(DIK_RIGHT)) { move.x = kCharacterSpeed; }

	if (input_->PushKey(DIK_UP)) { move.y = kCharacterSpeed; }
	else if (input_->PushKey(DIK_DOWN)) { move.y = -kCharacterSpeed; }

	worldTransform_.translation_ += move;
	// �������E���W
	const float kMoveLimitX = 35.0f;
	const float kMoveLimitY = 19.0f;
	// �͈͂𒴂��Ȃ�����
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
	MyFunc::Transform(worldTransform_, 0);
	// �f�o�b�O�p�\��
	debugText_->SetPos(50, 150);
	debugText_->Printf(
		"Root:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
}

void Player::Attack()
{
	if (input_->TriggerKey(DIK_SPACE))
	{
		// ���L�����̍��W���R�s�[
		Vector3 position = worldTransform_.translation_;
		// �e�𐶐����A������
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, position);
		// �e��o�^����
		bullets_.push_back(std::move(newBullet));
	}
}