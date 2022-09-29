#pragma once

#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "func/MyFunc.h"
#include "PlayerBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "math.h"
#include <cassert>
#include <memory>
#include <list>

class Player
{
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name = "model" > ���f�� </param>
	/// <param name = "textureHamdle" > �e�N�X�`���n���h�� </param>
	void Initialize(Model* model, uint32_t textureHandle);
	
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();

	/// <summary>
	/// �U��
	/// </summary>
	void Attack();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection viewPojection);

private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	// �r���[�v���_�N�V����
	ViewProjection viewProjection_;
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	// �e
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

};

