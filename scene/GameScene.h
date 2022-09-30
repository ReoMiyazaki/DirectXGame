#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "Enemy/Enemy.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Skydome/Skydome.h"
#include "Sprite.h"
#include "Player/Player.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include <DirectXMath.h>


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 3Dモデル
	Model* model_ = nullptr;
	// ビュープロダクション
	ViewProjection viewProjection_;
	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

	const float XM_PI = 3.1415;

	float viewAngle = 0.0f;

	// 自キャラ用
	Player* player_ = nullptr;
	// 敵キャラ用
	Enemy* enemy_ = nullptr;
	// 天球
	Skydome* skydome_ = nullptr;
	// 3Dモデル
	Model* modelSkydome_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	int sceneNum = 0;
};
