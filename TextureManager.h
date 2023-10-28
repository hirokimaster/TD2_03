#pragma once
#include <array>
#include "externals/DirectXTex/d3dx12.h"
#include <string>
#include <unordered_map>
#include <wrl.h>
#include "externals/DirectXTex/DirectXTex.h"
#include "StringUtility.h"
#include "DirectXCommon.h"

struct Texture {
	// テクスチャリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> texResource_;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
};

class TextureManager {
public:
	/// <summary>
	/// シングルトン
	/// </summary>
	/// <returns></returns>
	static TextureManager* GetInstance();

	/// <summary>
	/// 読み込み
	/// </summary>
	static uint32_t Load(const std::string& fileName);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 全テクスチャリセット
	/// </summary>
	/*void ResetAllTex();*/


private:
	TextureManager() = default;
	~TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	static DirectX::ScratchImage LoadTexture(const std::string& filePath);

	static ID3D12Resource* CreateTextureResource(const DirectX::TexMetadata& metadata);

	static void UploadTextureData(Microsoft::WRL::ComPtr<ID3D12Resource> texture, const DirectX::ScratchImage& mipImages);



};
