#pragma once
#include "IScene/IScene.h"
#include "Sprite/Sprite.h"
#include "ImGuiManager/ImGuiManager.h"
#include "Input/Input.h"
#include "Animation/Animation.h"

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
	uint32_t texHandleTitle_ = 0;
	std::unique_ptr<Animation> animation_ = nullptr;
	bool isAnimation_ = false;
	float sceneTimer_ = 130.0f;
};