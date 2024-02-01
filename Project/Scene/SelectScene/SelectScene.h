#pragma once
#include "IScene/IScene.h"
#include "ImGuiManager/ImGuiManager.h"
#include "Sprite/Sprite.h"
#include "Input/Input.h"
#include "Animation/Animation.h"

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
	uint32_t texHandleSelect_ = 0;
	uint32_t selectNum_ = 0;
	std::unique_ptr<Animation> animation_ = nullptr;
	bool isAnimation_ = false;
};
