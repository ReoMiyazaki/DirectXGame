#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	// NULL�|�C���^
	assert(model);
	model_ = model;
	velocity_ = velocity;
	// �e�N�X�`���n���h���ǂݍ���
	textureHandle_ = TextureManager::Load("blue.png");
	worldTransform_.Initialize();
	// �����Ŏ󂯎�������������W�����Z�b�g
	worldTransform_.translation_ = position;
}

void EnemyBullet::Update()
{
	// ���W���ړ�������
	worldTransform_.translation_ += velocity_;
	MyFunc::Matrix4(worldTransform_, 0);
	// ���Ԍo�߂Ńf�X
	if (--deathTimer_ <= 0) { isDead_ = true; }
}

void EnemyBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}