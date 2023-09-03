#include "WinApp.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp* win = new WinApp();

	// ウィンドウの作成
	win->CreateGameWindow(L"DirectXGame");

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ゲームの処理

	}

	return 0;
}