#pragma once

#include "DirectXCommon.h"
#include "StringUtility.h"
#include "ShaderCompile.h"
#include "Resource.h"

struct Property {
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> graphicsPipelineState_;
	Microsoft::WRL::ComPtr<ID3DBlob> signatureBlob_ = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob_ = nullptr;
};

class GraphicsPipeline {
public:

	// シングルトンインスタンスの取得
	static GraphicsPipeline* GetInstance();

	static void Initialize();

	static void CreateRootSignature(DirectXCommon* dxCommon, Property& property);

	Property GetProperty() { return property; }

	// Relese処理
	//void Relese();


private:
	
	static Property Triangle(DirectXCommon* dxCommon);

	Property property = {};
	
};
