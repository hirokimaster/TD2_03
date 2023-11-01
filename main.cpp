#include "WinApp.h"
#include "DirectXCommon.h"
#include "ShaderCompile.h"
#include "Sprite.h"
#include "GameScene.h"
#include "GraphicsPipeline.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include "Triangle.h"
#include "Model.h"
#include "ModelSphere.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// COMの初期化
	CoInitializeEx(0, COINIT_MULTITHREADED);
	
	WinApp* win = WinApp::GetInstance();
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Sprite* sprite = nullptr;
	Model* model = nullptr;

	// ゲームシーンの初期化
	//GameScene* gameScene = new GameScene();
	//gameScene->Initialize();
	
	// ウィンドウの作成
	win->CreateGameWindow(L"DirectXGame");
	// DirectX初期化
	dxCommon->Initialize(win);
	GraphicsPipeline::Initialize();
	TextureManager::GetInstance()->Initialize();

	model = Model::Create(new ModelSphere);

	sprite = Sprite::Create({ 200.0f,100.0f });

	uint32_t texHandle = TextureManager::Load("resources/uvChecker.png");
	uint32_t texHandle2 = TextureManager::Load("resources/monsterBall.png");


	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	WorldTransform transform;
	ViewProjection viewProjection;
	viewProjection.Initialize();
	transform.Initialize();

	
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
		viewProjection.UpdateMatrix();
		transform.UpdateMatrix();
		transform.rotate.y += 0.03f;

		imguiManager->End();

		// 描画前処理
		dxCommon->PreDraw();
		// ゲームシーン描画
		//gameScene->Draw();
		
		// スプライト複数描画
		sprite->Draw(viewProjection, texHandle);
	
		model->Draw(transform,viewProjection, texHandle);
		
		
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