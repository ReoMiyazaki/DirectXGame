#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position)
{
	// NULL�|�C���^
	assert(model);
	model_ = model;
	// �e�N�X�`���n���h���ǂݍ���
	textureHandle_ = TextureManager::Load("black.png");
	worldTransform_.Initialize();
	// �����Ŏ󂯎�������������W�����Z�b�g
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update()
{
	MyFunc::Transform(worldTransform_, 0);
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
