#pragma once
#include "Sprite.h"
#include "Triangle.h"
#include "Model.h"
#include "ModelSphere.h"
#include "ModelCube.h"
#include "Input.h"
#include "ImGuiManager/ImGuiManager.h"
#include "IScene/IScene.h"

#include "Enemy/Enemy.h"
#include "Player/Player.h"
#include "Player/PlayerParticle.h"

#include<random>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene : public IScene {

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
	void Initialize()override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	void CameraShake();

private: // メンバ変数
	std::unique_ptr<Enemy> enemy_;
	std::unique_ptr<Player> player_;
	Camera camera_;

	float shakeTime = 0;
	bool IsShake = false;	//画面の揺れ　true : 振る

};
