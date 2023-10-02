#pragma once
#include "DirectXCommon.h"
#include "StringUtility.h"
#include "ShaderCompile.h"

class Sprite {
public: // メンバ変数

	// シングルトンインスタンスの取得
	static Sprite* GetInstance();

	//初期化
	void Initialize(DirectXCommon* dxCommon);

	// グラフィックペーパーライン初期化
	void InitializeGraphicsPipeline();

	// 三角形描画
	void DrawTriangle(DirectXCommon* dxCommon);

	// Relese処理
	void Relese();

private: // メンバ変数
	HRESULT hr_;
	DirectXCommon* dxCommon_;
	ID3DBlob* signatureBlob_ = nullptr;
	ID3DBlob* errorBlob_ = nullptr;
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> graphicsPipelineState;
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_;
	ShaderCompile* compile_;
	IDxcBlob* vertexShaderBlob_;
	IDxcBlob* pixelShaderBlob_;
	// 頂点バッファビューを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	// ビューポート
	D3D12_VIEWPORT viewport{};
	// シザー矩形
	D3D12_RECT scissorRect{};
};
