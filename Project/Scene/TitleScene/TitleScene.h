#pragma once
#include "IScene/IScene.h"
#include "Sprite/Sprite.h"
#include "ImGuiManager/ImGuiManager.h"
#include "Input/Input.h"
#include "Animation/Animation.h"
#include "GameManager.h"
#include "SelectScene/SelectScene.h"
#include"Audio/Audio.h"

class TitleScene : public IScene {
public:
	TitleScene();
	~TitleScene();
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
	std::unique_ptr<Sprite> spriteTitle_ = nullptr;
	std::unique_ptr<Sprite> spriteA_ = nullptr;
	std::unique_ptr<Sprite> spriteStart_ = nullptr;
	uint32_t texHandleA_ = 0;
	uint32_t texHandleStart_ = 0;
	uint32_t texHandleTitle_ = 0;

	uint32_t titleBGM = 0;
	uint32_t clickSound = 0;

	bool isAnimation_ = false;
	float sceneTimer_ = 130.0f;
	uint32_t startATimer_ = 0;
};