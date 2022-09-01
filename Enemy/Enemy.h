#pragma once

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

};