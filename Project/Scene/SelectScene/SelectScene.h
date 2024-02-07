#pragma once
#include "IScene/IScene.h"
#include "ImGuiManager/ImGuiManager.h"
#include "Sprite/Sprite.h"
#include "Input/Input.h"
#include "Animation/Animation.h"
#include "GameManager.h"

class SelectScene : public IScene {
public:

	SelectScene();
	~SelectScene();

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
	std::unique_ptr<Sprite> spriteSelect_ = nullptr;
	std::unique_ptr<Sprite> spriteS_ = nullptr;
	uint32_t texHandleSelect1_ = 0;
	uint32_t texHandleSelect2_ = 0;
	uint32_t texHandleSelect3_ = 0;
	uint32_t texHandleSelect_ = 0;
	uint32_t texHandleS_ = 0;
	uint32_t selectNum_ = 0;
	bool isAnimation_ = false;
	bool isFadeIn_ = false;
	float sceneTimer_ = 130.0f;
};
