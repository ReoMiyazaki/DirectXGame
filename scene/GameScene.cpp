#include "AxisIndicator.h"
#include "GameScene.h"
#include "MyFunc/MyFunc.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "MyFunc/affine.h"
#include <cassert>
#include <random>

GameScene::GameScene() {}

GameScene::~GameScene()
{
	delete model_;
	delete debugCamera_;
	delete player_;
	delete enemy_;
	delete skydome_;
	delete modelSkydome_;
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

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	// デバックカメラ
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	// ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_);
	// 敵キャラの生成
	enemy_ = new Enemy();
	// 敵キャラの初期化
	enemy_->Initialize(model_, textureHandle_);
	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);
	// 天球の生成
	skydome_ = new Skydome();
	// 3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	// 天球の初期化
	skydome_->Initialize(modelSkydome_);

}

void GameScene::Update()
{
	debugCamera_->Update();
	if (sceneNum == 0 && input_->TriggerKey(DIK_SPACE)) { sceneNum = 1; }
	else if (sceneNum == 1 && enemy_->hp == 0 || player_->hp == 0)
	{
		if (enemy_->hp == 0) { sceneNum = 2; }
		else if (player_->hp == 0) { sceneNum == 3; }
	}

	if (sceneNum == 1) {

		// 自キャラの更新
		player_->Update();

		enemy_->UpDate();

		CheckAllCollisions();
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

	// 自キャラの描画
	if (sceneNum == 1) {

		player_->Draw(viewProjection_);

		enemy_->Draw(viewProjection_);
	}


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

	if (sceneNum == 0) {
		debugText_->SetPos(300, 200);
		debugText_->Printf("Push space  GameStart");
	}
	else if (sceneNum == 1) {
		debugText_->SetPos(100, 100);
		debugText_->Printf("Enemy HP : %d",enemy_->hp);
		debugText_->SetPos(100, 300);
		debugText_->Printf("Player HP : %d", player_->hp);
	}
	else if (sceneNum == 2) {
		debugText_->SetPos(300, 300);
		debugText_->Printf("you win\nPlease Press");
	}
	else if (sceneNum == 3) {
		debugText_->SetPos(300, 300);
		debugText_->Printf("you lose\nPlease Press");
	}
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions()
{

	//判定対象aとbの座標
	Vector3 posA, posB;

	//自機弾リストの取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullet = player_->GetBulletd();
	//敵の弾リストの取得
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullet = enemy_->GetBulletd();

#pragma region 自キャラと敵弾の当たり判定
	//自キャラ座標
	posA = player_->GetWorldPosition();

	//自キャラと敵弾
	for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullet) {
		posB = bullet.get()->GetWorldPosition();

		float x = posA.x - posB.x;
		float y = posA.y - posB.y;
		float z = posA.z - posB.z;

		float distance = sqrt(x * x + y * y + z * z);

		Matrix4 matA = player_->GetMatrix();
		Matrix4 matB = bullet->GetMatrix();

		//弾と弾の交差判定
		if (distance < matA.m[0][0] + matB.m[0][0]) {	//スケールxを半径として使用
			player_->OnCollision();
			bullet->OnCollision();
		}

	}
#pragma endregion


#pragma region 自弾と敵キャラの当たり判定
	//自キャラ座標
	posA = enemy_->GetWorldPosition();

	//自キャラと敵弾
	for (const std::unique_ptr<PlayerBullet>& bullet : playerBullet) {
		posB = bullet.get()->GetWorldPosition();

		float x = posA.x - posB.x;
		float y = posA.y - posB.y;
		float z = posA.z - posB.z;

		float distance = sqrt(x * x + y * y + z * z);

		Matrix4 matA = enemy_->GetMatrix();
		Matrix4 matB = bullet->GetMatrix();

		//弾と弾の交差判定
		if (distance <= matA.m[0][0] + matB.m[0][0]) {	//スケールxを半径として使用
			enemy_->OnCollision();
			bullet->OnCollision();
		}

	}
#pragma endregion
}
