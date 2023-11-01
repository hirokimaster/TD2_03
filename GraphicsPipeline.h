#pragma once

#include "DirectXCommon.h"
#include "StringUtility.h"
#include "ShaderCompile.h"
#include "CreateResource.h"

// 共通
struct Property {
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_ = nullptr;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> graphicsPipelineState_ = nullptr;;
	Microsoft::WRL::ComPtr<ID3DBlob> signatureBlob_ = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob_ = nullptr;
};

struct PipelineState {
	Property triangle;
	Property Sprite2D;
};

class GraphicsPipeline {
public:

	// シングルトンインスタンスの取得
	static GraphicsPipeline* GetInstance();

	static void Initialize();

	PipelineState GetPs() { return  ps; }


private:
	
	static void CreateRootSignature(Microsoft::WRL::ComPtr <ID3D12Device> device, D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature, Property& property);

	static void CreatePipeline(PipelineState& ps);

	static Property CreateTriangle(Microsoft::WRL::ComPtr <ID3D12Device> device, const std::wstring& shaderName);

	static Property CreateSprite2D(Microsoft::WRL::ComPtr <ID3D12Device> device, const std::wstring& shaderName);

	PipelineState ps = {};

};
