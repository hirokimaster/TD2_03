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
#include "Animation/Animation.h"
#include "Ring/Ring.h"
#include "GameManager.h"

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
	std::unique_ptr<Sprite> spriteUI_;
	std::unique_ptr<Sprite> spriteHp_[3];
	uint32_t texHandleUI_ = 0;
	uint32_t texHandleHp_ = 0;
	PointLight pointLight_{}; // ライト用

	std::unique_ptr<Ring> ring_;


	Camera camera_;

	float shakeTime = 0;
	bool IsShake = false;	//画面の揺れ　true : 振る

	bool isFadeIn_ = false;
	float sceneTimer_ = 130.0f;
	std::unique_ptr<Sprite> spriteA_ = nullptr;
	std::unique_ptr<Sprite> spriteReturn_ = nullptr;
	uint32_t texHandleA_ = 0;
	uint32_t texHandleReturn_ = 0;
	uint32_t startATimer_ = 0;
	bool isKO_;
	float koTimer_ = 180.0f;

};
