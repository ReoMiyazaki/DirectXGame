#pragma once

#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyFunc/MyFunc.h"
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

	// ����
	void Rotate();
	// �ړ�
	void Move();
	// �U��
	void Attack();
	
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection viewPojection);

	Vector3 RotationOperator(Vector3& velocity, WorldTransform& worldTransform);
	// ���[���h���W���擾
	Vector3 GetWorldPosition();

	void OnCollision();

	//�e���X�g
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	void DeleteBullet();



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

