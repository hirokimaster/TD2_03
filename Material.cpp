#include "Material.h"

Microsoft::WRL::ComPtr<ID3D12Resource> Material::CreateMaterial(Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource){

	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_;
	// 頂点リソースにデータを書き込む
	Vector4* vertexData = nullptr;
	// 書き込むためのアドレスを取得
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	// 左下
	vertexData[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
	// 上
	vertexData[1] = { 0.0f, 0.5f, 0.0f, 1.0f };
	// 右下
	vertexData[2] = { 0.5f, -0.5f, 0.0f, 1.0f };

	materialResource_ = CreateResource::CreateBufferResource(sizeof(Vector4));
	// データを書き込む
	Vector4* materialData = nullptr;
	// アドレスを取得
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	// 赤
	*materialData = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

	return materialResource_;

}
