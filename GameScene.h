#pragma once
#include "Sprite.h"
#include "Triangle.h"
#include "Model.h"
#include "ModelSphere.h"

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

private: // メンバ変数

	Sprite* sprite = nullptr;
	Model* model = nullptr;
	Sprite* sprite2 = nullptr;

	WorldTransform transform;
	ViewProjection viewProjection;

	uint32_t texHandle = TextureManager::Load("resources/uvChecker.png");
	uint32_t texHandle2 = TextureManager::Load("resources/monsterBall.png");

};
