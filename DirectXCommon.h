#pragma once

#include <Windows.h>
#include <cstdint>
#include <format>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <wrl.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#include "WinApp.h"

class DirectXCommon {
public : // メンバ関数

	DirectXCommon() = default;
	~DirectXCommon() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp* win);

private:
	WinApp* winApp_;
	// dxgifactory
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_;
	// device
	Microsoft::WRL::ComPtr<ID3D12Device> device_;

};