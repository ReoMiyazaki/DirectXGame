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

void Player::Rotate()
{
	const float kRotateSpd = 0.02f;

	if (input_->PushKey(DIK_D)) { worldTransform_.rotation_.y -= kRotateSpd; }
	else if (input_->PushKey(DIK_A)) { worldTransform_.rotation_.y += kRotateSpd; }
}

void Player::Move()
{
	// �L�����N�^�[�ړ��̑���
	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) { worldTransform_.translation_.x -= kCharacterSpeed; }
	else if (input_->PushKey(DIK_RIGHT)) { worldTransform_.translation_.x += kCharacterSpeed; }

	if (input_->PushKey(DIK_UP)) { worldTransform_.translation_.y += kCharacterSpeed; }
	else if (input_->PushKey(DIK_DOWN)) { worldTransform_.translation_.y -= kCharacterSpeed; }

	// �������E���W
	const float kMoveLimitX = 35.0f;
	const float kMoveLimitY = 19.0f;
	// �͈͂𒴂��Ȃ�����
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
	// �f�o�b�O�p�\��
	debugText_->SetPos(50, 150);
	debugText_->Printf(
		"Root:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
}

void Player::Attack()
{
	if (input_->PushKey(DIK_SPACE))
	{
		// �e�𐶐����A������
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);
		// �e��o�^����
		bullet_ = newBullet;
	}
}

void Player::Update()
{
	Move();
	Rotate();
	Attack();
	// �e�X�V
	if (bullet_) { bullet_->Update(); }
	MyFunc::Transform(worldTransform_, 0);
}

void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	// �e�`��
	if (bullet_) { bullet_->Draw(viewProjection); }
}