#include "WinApp.h"
#include "DirectXCommon.h"
#include "ShaderCompile.h"
#include "Mesh.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp* win = WinApp::GetInstance();
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Mesh* mesh = Mesh::GetInstance();
	
	// ウィンドウの作成
	win->CreateGameWindow(L"DirectXGame");
	// DirectX初期化
	dxCommon->Initialize(win);
	// メッシュ初期化
	mesh->Initialize(dxCommon);
	
	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ゲームの処理

		// 描画前処理
		dxCommon->PreDraw();

		// 三角形描画
		mesh->DrawTriangle(dxCommon);

		// 描画後処理
		dxCommon->PostDraw();


	}

	// 出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");

	// リリース
	mesh->Relese();

	return 0;
}