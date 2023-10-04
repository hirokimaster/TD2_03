#pragma once
/*
#include "DirectXCommon.h"
#include "StringUtility.h"
#include "ShaderCompile.h"
#include "Resource.h"

class GraphicsPipeline {
public:

	// シングルトンインスタンスの取得
	static GraphicsPipeline* GetInstance();

	void Initialize();

	// マテリアルリソース取得
	ID3D12Resource* GetMaterialResource() const { return materialResource_.Get(); }
	// vertexresource取得
	ID3D12Resource* GetVertexResource() const { return vertexResource_.Get(); }

	ID3D12PipelineState* GetPipelineState() const { return graphicsPipelineState_.Get(); }

	ID3D12RootSignature* GetRootSignature() const { return rootSignature_.Get(); }

	// Relese処理
	void Relese();


private:

	HRESULT hr_;
	DirectXCommon* dxCommon_;
	ID3DBlob* signatureBlob_ = nullptr;
	ID3DBlob* errorBlob_ = nullptr;
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> graphicsPipelineState_;
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_;
	ShaderCompile* compile_;
	IDxcBlob* vertexShaderBlob_;
	IDxcBlob* pixelShaderBlob_;
	// 頂点バッファビューを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	// ビューポート
	D3D12_VIEWPORT viewport{};
	// シザー矩形
	D3D12_RECT scissorRect{};
};*/
