#include "AxisIndicator.h"
#include "GameScene.h"
#include "TextureManager.h"
#include "PrimitiveDrawer.h"
#include "affine.h"
#include <cassert>
#include <random>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("MagicCircle.jpg");
	// 3Dモデルの生成
	model_ = Model::Create();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjention_.Initialize();
	// デバックカメラ
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
	// ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

	affine::AffineMat affineMat;
	Vector3 scale = { 5,5,5 };
	Vector3 rotation = { XM_PI / 4,XM_PI / 4, XM_PI / 4, };
	Vector3 transform = { 10, 10, 10 };

	worldTransform_.scale_ = scale;
	worldTransform_.rotation_ = rotation;
	worldTransform_.translation_ = transform;

	affine::setScaleMat(affineMat.scale, worldTransform_);
	affine::setRotateMat(affineMat, worldTransform_);
	affine::setTransformMat(affineMat.transform, worldTransform_);
	worldTransform_.matWorld_ = MathUtility::Matrix4Identity();
	affine::setTransformationWorldMat(affineMat, worldTransform_);

	worldTransform_.TransferMatrix();
}

void GameScene::Update() { debugCamera_->Update(); }

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	model_->Draw(worldTransform_, viewProjention_, textureHandle_);
	//	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
	//	for (int i = 0; i <= 10; i++) {
	//		PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(-5.0f, -5.0f + 1.0f * i, 0.0f), Vector3(5.0, -5.0f + 1.0f * i, 0.0f), Vector4(1.0f, 0.0f, 0.0f, 1));
	//	}
	//	for (int j = 0; j <= 10; j++) {
	//		PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(-5.0f + 1.0f * j, -5.0f, 0.0f), Vector3(-5.0f + 1.0f * j, 5.0f, 0.0f), Vector4(0.0f, 0.0f, 1.0f, 1));
	//	}

		// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
