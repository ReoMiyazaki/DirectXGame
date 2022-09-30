#pragma once

#include "Model.h"
#include "MyFunc/MyFunc.h"
#include "WorldTransform.h"
#include <cassert>


/// <summary>
/// �V��
/// </summary>
class Skydome
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection viewProjection);

private:
	// ���[���h�Ԋ҃f�[�^
	WorldTransform worldTransform_;
	// 
	ViewProjection viewProjection_;
	// ���f��
	Model* model_ = nullptr;
};