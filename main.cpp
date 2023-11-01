#include "WinApp.h"
#include "DirectXCommon.h"
#include "ShaderCompile.h"
#include "GameScene.h"
#include "GraphicsPipeline.h"
#include "ImGuiManager.h"
#include "TextureManager.h"


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// COMの初期化
	CoInitializeEx(0, COINIT_MULTITHREADED);
	
	WinApp* win = WinApp::GetInstance();
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	
	// ウィンドウの作成
	win->CreateGameWindow(L"DirectXGame");
	// DirectX初期化
	dxCommon->Initialize(win);
	GraphicsPipeline::Initialize();
	TextureManager::GetInstance()->Initialize();

	// ゲームシーンの初期化
	GameScene* gameScene = new GameScene();
	gameScene->Initialize();

	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		//imgui受付開始
		imguiManager->Begin();
		// 開発用のUIの処理。実際に開発用のUIを出す場合はここをゲーム固有の処理に置き換える
		ImGui::ShowDemoWindow();

		// ゲームの処理
		gameScene->Update();

		imguiManager->End();

		// 描画前処理
		dxCommon->PreDraw();

		// ゲームシーン描画
		gameScene->Draw();
		
		imguiManager->Draw();
		// 描画後処理
		dxCommon->PostDraw();


	}

	imguiManager->Finalize();

	// COMの終了処理
	CoUninitialize();

	CloseWindow(win->GetHwnd());

	return 0;
}