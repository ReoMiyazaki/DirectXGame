#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{

	// �����V�[�h������
//	std::random_device seed_gen;
	// �����Z���k�E�c�C�X�^�[�̗����G���W��
//	std::mt19937_64 engin(seed_gen());
	// �����͈͂̎w��
//	std::uniform_real_distribution<float> trans(-10, 10);

	// NULL�|�C���^�`�F�b�N
	assert(model);
	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	this->model_ = model;
	this->textureHandle_ = textureHandle;
	// ���[���h�ϊ��̏�����
	worldTransform_.Initialize();
//	worldTransform_.translation_ = { trans(engin), trans(engin), trans(engin) };
}
void Enemy::UpDate()
{
	MyFunc::Matrix4(worldTransform_, 0);
}

void Enemy::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
