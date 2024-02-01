#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "ShaderCompile.h"
#include "GraphicsPipeline.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include "Input.h"
#include "Audio/Audio.h"
#include "GameManager.h"

class Framework {
public:
	virtual ~Framework() = default;
	virtual void Initialize();
	virtual void Finalize();
	virtual void Update();
	virtual void Draw() = 0;

	void Run();

private:
	WinApp* win_;
	DirectXCommon* dxCommon_;
	Audio* audio_;
	ImGuiManager* imguiManager_;
	GameManager* gameManager_ = nullptr;
};
