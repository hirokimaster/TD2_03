#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "ShaderCompile.h"
#include "GameManager.h"
#include "GraphicsPipeline.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include "Input.h"
#include "Audio/Audio.h"

class Engine {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// 更新処理
	/// </summary>
	void Run();

	/// <summary>
	/// 終了
	/// </summary>
	int Finalize();

private:
	WinApp* win_;
	DirectXCommon* dxCommon_;
	Audio* audio_;
	ImGuiManager* imguiManager_;
	std::unique_ptr<GameManager> gameManager_;
};
