#pragma once
#include "Sprite.h"
#include "Model.h"
#include "Input.h"
#include "ImGuiManager/ImGuiManager.h"
#include "IScene/IScene.h"
#include "Player.h"

using namespace std;

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
	ViewProjection viewProjection_ = {};
	unique_ptr<Model> modelPlayer_;
	unique_ptr<Player> player_;
	unique_ptr<PlayerBullet> playerBullet_;
	uint32_t texHandlePlayer_ = 0;
};
