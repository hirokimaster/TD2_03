#pragma once
#include "DirectXCommon.h"
#include "StringUtility.h"
#include "ShaderCompile.h"
#include "CreateResource.h"
#include "GraphicsPipeline.h"
#include "Material.h"
#include "Matrix4x4.h"
#include "Mathfunction.h"
#include "WorldTransform.h"

class Sprite {
public: // メンバ変数

	// シングルトンインスタンスの取得
	static Sprite* GetInstance();

	//初期化
	void Initialize();

	// 三角形描画
	void DrawTriangle(WorldTransform worldTransform);

private: // メンバ変数

	D3D12_VERTEX_BUFFER_VIEW VBV{};
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_;
	Resource resource_ = {};
	WorldTransform worldTransform_ = {};

};
