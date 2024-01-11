#pragma once
#include "IScene/IScene.h"
#include "Sprite/Sprite.h"
#include "ImGuiManager/ImGuiManager.h"
#include "Input/Input.h"

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
	std::unique_ptr<Sprite> spriteBlack_ = nullptr;
	uint32_t texHandleTitle_ = 0;
	uint32_t texHandleBlack_ = 0;
	uint32_t sceneTimer_ = 0;
	bool timerFlag_ = false;
	Vector4 color_ = {};
};