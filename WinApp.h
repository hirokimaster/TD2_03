#pragma once
#include <Windows.h>
#include <cstdint>

class WinApp {
public: // 静的メンバ変数
	// ウィンドウサイズ
	static const int32_t kWindowWidth = 1280; // 横
	static const int32_t kWindowHeight = 720; // 縦

	// ウィンドウクラス名
	static const wchar_t kWindowClassName[];

public: // メンバ関数

	// ウィンドウプロシージャ
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	// メッセージ処理
	bool ProcessMessage();

	// ウィンドウを作る
	void CreateGameWindow(
		const wchar_t* title = L"DirectXGame", UINT windowStyle = WS_OVERLAPPEDWINDOW,
		int32_t clientWidth = kWindowWidth, int32_t clientHeight = kWindowHeight);

private: // メンバ変数

	// Window関連
	HWND hwnd_ = nullptr;   // ウィンドウハンドル
	WNDCLASS wc{}; // ウィンドウクラス
	UINT windowStyle_;
	
};

