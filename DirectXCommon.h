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

	// シングルトンインスタンスの取得
	static DirectXCommon* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp* win);

	// DXGI初期化
	void InitializeDxgi();

	// コマンド
	void InitializeCommand();

	// スワップチェーン
	void CreateSwapChain();

	// RTV作成
	void CreateRenderTargetView();

	// fence作成
	void CreateFence();

private:
	WinApp* winApp_;
	// DirectX3D関連
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_;
	Microsoft::WRL::ComPtr<ID3D12Device> device_;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList_;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator_;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain_;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap_;
	Microsoft::WRL::ComPtr<ID3D12Fence> fence_;
	UINT64 fenceVal_ = 0;
	HANDLE fenceEvent_;
	
};