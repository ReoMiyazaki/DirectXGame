#include "AxisIndicator.h"
#include "GameScene.h"
#include "MyFunc.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "affine.h"
#include <cassert>
#include <random>

GameScene::GameScene() {}

GameScene::~GameScene()
{
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("MagicCircle.jpg");
	// 3Dモデルの生成
	model_ = Model::Create();
	for (WorldTransform& worldTransform : worldTransforms_)
	{
		// ワールドトランスフォームの初期化
		worldTransform.Initialize();
	}

	// カメラの視点座標を設定
//	viewProjention_.eye = { 0, 0, -10 };
	// カメラ視点座標を固定
	viewProjention_.target = { 10, 0, 0 };
	// カメラ上方向ベクトル設定
	viewProjention_.up = { cosf(XM_PI / 4), sinf(XM_PI / 4), 0.0f };

	// ビュープロジェクションの初期化
	viewProjention_.Initialize();
	// デバックカメラ
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjention_);
	// ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

	// 乱数シード生成器
	std::random_device seed_gen;
	// メルセンヌ・ツイスターの乱数エンジン
	std::mt19937_64 engin(seed_gen());
	// 乱数範囲の指定
	std::uniform_real_distribution<float> rot(0, XM_PI);
	std::uniform_real_distribution<float> trans(-10, 10);

	for (WorldTransform& worldTransform : worldTransforms_)
	{
		Vector3 scale = { 1,1,1 };
		Vector3 rotation = { rot(engin), rot(engin), rot(engin) };
		Vector3 transform = { trans(engin), trans(engin), trans(engin) };
		worldTransform.scale_ = scale;
		worldTransform.rotation_ = rotation;
		worldTransform.translation_ = transform;
		MyFunc::Transform(worldTransform, 0);
	}

}

void GameScene::Update()
{
	debugCamera_->Update();

	// 視点移動処理
	{
		// 視点移動ベクトル
		Vector3 move = { 0.0f, 0.0f, 0.0f };
		// 視点の速さ
		const float kEyeSpeed = 0.2f;
		// 押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_W)) { move.z += kEyeSpeed; }
		else if (input_->PushKey(DIK_S)) { move.z -= kEyeSpeed; }
		// 視点移動(ベクトルの加算)
		viewProjention_.eye += move;
		// 行列の再計算
		viewProjention_.UpdateMatrix();
		// デバック用表示
		debugText_->SetPos(50, 50);
		debugText_->Printf("eye:(%f, %f, %f)", viewProjention_.eye.x, viewProjention_.eye.y, viewProjention_.eye.z);
	}
	// 中視点移動処理
	{
		// 注視点移動ベクトル
		Vector3 move = { 0.0f, 0.0f, 0.0f };
		// 注視点の速さ
		const float kTargetSpeed = 0.2f;
		// 押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_LEFT)) { move.x -= kTargetSpeed; }
		else if (input_->PushKey(DIK_RIGHT)) { move.x += kTargetSpeed; }
		//注視点の移動
		viewProjention_.target += move;
		// 行列の再計算
		viewProjention_.UpdateMatrix();
		// デバック用表示
		debugText_->SetPos(50, 70);
		debugText_->Printf("target:(%f, %f, %f)", viewProjention_.target.x, viewProjention_.target.y, viewProjention_.target.z);
	}
	// 上方向回転処理
	{
		// 上方向の回転速さ[ラジアン/frame]
		const float kUpRotSpeed = 0.05f;
		// 押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_SPACE))
		{
			viewAngle += kUpRotSpeed;
			// 2πを超えたら0に戻す
			viewAngle = fmodf(viewAngle, XM_PI * 2.0f);
		}
		// 上方向ベクトルを計算(半径1の円周上の座標)
		viewProjention_.up = { cosf(viewAngle), sinf(viewAngle), 0.0f };
		// 行列の再計算
		viewProjention_.UpdateMatrix();
		// デバック用表示
		debugText_->SetPos(50, 90);
		debugText_->Printf("up:(%f, %f, %f)", viewProjention_.up.x, viewProjention_.up.y, viewProjention_.up.z);
	}

}

void GameScene::Draw()
{
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
	for (WorldTransform& worldTransform : worldTransforms_)
	{
		model_->Draw(worldTransform, viewProjention_, textureHandle_);
	}
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
