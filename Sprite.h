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
#include "ViewProjection.h"
#include "TextureManager.h"

class Sprite {
public: // メンバ変数

	// シングルトンインスタンスの取得
	static Sprite* GetInstance();

	//初期化
	void Initialize();

	// 三角形描画
	void DrawTriangle(WorldTransform worldTransform, ViewProjection viewProjection, uint32_t texHandle);

private: // メンバ変数

	D3D12_VERTEX_BUFFER_VIEW VBV{};
	Resource resource_ = {};
	WorldTransform worldTransform_ = {};

};
