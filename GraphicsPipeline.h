#pragma once

#include "DirectXCommon.h"
#include "StringUtility.h"
#include "ShaderCompile.h"
#include "Resource.h"

struct Property {
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> graphicsPipelineState_;
	Microsoft::WRL::ComPtr<ID3DBlob> signatureBlob_;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob_;
};


class GraphicsPipeline {
public:

	// シングルトンインスタンスの取得
	static GraphicsPipeline* GetInstance();

	static void Initialize();

	Property GetProperty() { return property; }

	
	// Relese処理
	//void Relese();


private:
	
	static void CreateRootSignature(D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature, Property& property);

	static Property Triangle(Property property);

	Property property = {};
};
