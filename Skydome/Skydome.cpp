#include "Skydome.h"

void Skydome::Initialize(Model* model)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);
	this->model_ = model;
	worldTransform_.Initialize();
}

void Skydome::Update() {}

void Skydome::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}