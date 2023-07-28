#pragma once
#include <Windows.h>
#include <cstdint>

class WinApp {
public: // 静的メンバ変数
	// ウィンドウサイズ
	static const int32_t kWindowWidth = 1280; // 横
	static const int32_t kWindowHeight = 720; // 縦

public: // 静的メンバ関数

	// シングルトンインスタンス
	static WinApp* GetInstance();

	// ウィンドウプロシージャ
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

};

