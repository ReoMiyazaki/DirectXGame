#include "affine.h"
#include "MyFunc.h"

void MyFunc::Transform(WorldTransform& worldTransform, int i)
{
	affine::AffineMat affineMat;
	// スケーリング・回転・平行移動
	affine::setScaleMat(affineMat.scale, worldTransform);
	affine::setRotateMat(affineMat, worldTransform);
	affine::setTransformMat(affineMat.transform, worldTransform);
	worldTransform.matWorld_ = MathUtility::Matrix4Identity();
	affine::setTransformationWorldMat(affineMat, worldTransform);
	if (i != 0) 
	{
		// ワールド行列をかけて代入
		worldTransform.matWorld_ *= worldTransform.parent_->matWorld_;
	}
	// ワールド変換行列を転送
	worldTransform.TransferMatrix();
}