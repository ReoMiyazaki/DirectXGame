#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{

	// �����V�[�h������
	std::random_device seed_gen;
	// �����Z���k�E�c�C�X�^�[�̗����G���W��
	std::mt19937_64 engin(seed_gen());
	// �����͈͂̎w��
	std::uniform_real_distribution<float> trans(-10, 10);

	// NULL�|�C���^�`�F�b�N
	assert(model);
	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	this->model_ = model;
	this->textureHandle_ = textureHandle;
	// ���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	worldTransform_.translation_ = { trans(engin), trans(engin), 50 };
}

void Enemy::Approach()
{
	//�ڋߑ��x
	Vector3 approach_ = { 0.0f, 0.0f, -0.1f };

	worldTransform_.translation_ += approach_;
	//����̈ʒu�ɓ��B�����痣�E
	if (worldTransform_.translation_.z <= 0.0f)
	{
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave()
{
	//���E���x
	Vector3 leave_ = { -0.15f,0.1f,0.1f };

	worldTransform_.translation_ += leave_;
}

void Enemy::UpDate()
{
	MyFunc::Matrix4(worldTransform_, 0);
	switch (phase_) {
	case Phase::Approach://�ڋ߃t�F�[�Y
	default:
		//�ړ�
		Approach();
		break;

	case Phase::Leave://���E�t�F�[�Y
		Leave();
		break;
	}
}

void Enemy::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
