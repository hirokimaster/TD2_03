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

private: // メンバ変数
	std::unique_ptr<Enemy> enemy_;
	std::unique_ptr<Player> player_;
	/*-------------------------------
		  クリア演出用のやつ
	----------------------------------*/
	std::unique_ptr<Sprite>	spriteK_ = nullptr;
	std::unique_ptr<Sprite> spriteO_ = nullptr;
	uint32_t texHandleSpriteK_ = 0;
	uint32_t texHandleSpriteO_ = 0;
	Vector2 scaleK_{};
	Vector2 scaleO_{};
	bool isMoveK_ = false;
	bool isMoveO_ = false;
	float frameK_ = 0.0f;
	float endFrameK_ = 120.0f;
	float frameO_ = 0.0f;
	float endFrameO_ = 90.0f;

	/// ↑ここまで

	PointLight pointLight_{}; // ライト用
	Camera camera_;
};
