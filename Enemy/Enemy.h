#pragma once

#include "EnemyBullet.h"
#include "Model.h"
#include "MyFunc/MyFunc.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>

class Enemy
{
	enum class Phase
	{
		None,
		Approach,	//�ڋ߂���
		Leave,		//���E����
	};

public:
	// ������
	void Initialize(Model* model, uint32_t textureHandle);
	// �ڋ�
	void Approach();
	// ���E
	void Leave();
	// �e����
	void Fire();
	// �X�V
	void UpDate();
	// �`��
	void Draw(ViewProjection viewProjection);

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//�G�̍s���p�^�[��
	Phase phase_ = Phase::None;

	// �e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	//�ł��o���܂ł̎���
	float coolTimer = 0.0f;

};