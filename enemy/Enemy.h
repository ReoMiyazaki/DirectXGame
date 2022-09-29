#pragma once

#include "Model.h"
#include "MyFunc.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>

class Enemy
{

public:
	void Initialize(Model* model, uint32_t textureHandle);
	void UpDate();
	void Draw(ViewProjection viewProjection);

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

};