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
	MyFunc::Matrix4(worldTransform_, 0);
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
		// �e�̑��x 
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		velocity = RotationOperator(velocity, worldTransform_);
		// �e�𐶐����A������
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, position, velocity);
		// �e��o�^����
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

	// �e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) { bullet->Update(); }

	// �ł��t���O�̗������e���폜
//	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {return bullet->IsDead(); });
}

void Player::DeleteBullet()
{
	// �f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {return bullet->IsDead(); });
}


void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	// �e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) { bullet->Draw(viewProjection); }
}

Vector3 Player::RotationOperator(Vector3& velocity, WorldTransform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//����
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
	//���[���h���W�����邽�߂̕ϐ�
	Vector3 worldPos;

	//���[���h�s��̕��s�ړ��������擾
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
