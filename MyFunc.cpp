#include "affine.h"
#include "MyFunc.h"

void MyFunc::Transform(WorldTransform& worldTransform, int i)
{
	affine::AffineMat affineMat;
	// �X�P�[�����O�E��]�E���s�ړ�
	affine::setRotateMat(affineMat, worldTransform);
	affine::setTransformMat(affineMat.transform, worldTransform);
	affine::setScaleMat(affineMat.scale, worldTransform);
	worldTransform.matWorld_ = MathUtility::Matrix4Identity();

	if (i != 0) 
	{
		// ���[���h�s��������đ��
		worldTransform.matWorld_ *= worldTransform.parent_->matWorld_;
	}
	// ���[���h�ϊ��s���]��
	worldTransform.TransferMatrix();
}