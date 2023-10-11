#pragma once
#include "DirectXCommon.h"
#include "StringUtility.h"
#include "ShaderCompile.h"
#include "Resource.h"
#include "GraphicsPipeline.h"

class Sprite {
public: // メンバ変数

	// シングルトンインスタンスの取得
	static Sprite* GetInstance();

	//初期化
	void Initialize();

	// 三角形描画
	void DrawTriangle(DirectXCommon* dxCommon);

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	D3D12_VERTEX_BUFFER_VIEW VBV{};
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_;
	// ビューポート
	D3D12_VIEWPORT viewport{};
	// シザー矩形
	D3D12_RECT scissorRect{};
};
