#include "WinApp.h"
#include "DirectXCommon.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp* win = WinApp::GetInstance();
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// ウィンドウの作成
	win->CreateGameWindow(L"DirectXGame");
	// DirectX初期化
	dxCommon->Initialize(win);
	
	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ゲームの処理


	}

	// 出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");

	return 0;
}