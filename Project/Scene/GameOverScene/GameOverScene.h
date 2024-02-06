#pragma once
#include "IScene/IScene.h"
#include "Sprite.h"
#include "ImGuiManager/ImGuiManager.h"
#include "Input/Input.h"
#include "GameManager.h"

class GameOverScene : public IScene{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

private:
	Camera camera_{};
	std::unique_ptr<Sprite> spriteGameOver_ = nullptr;
	uint32_t texHandleGameOver_ = 0;

};

