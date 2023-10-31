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
#include "Vector2.h"

class Sprite {
public: // メンバ関数

	// シングルトンインスタンスの取得
	static Sprite* GetInstance();

	// 初期化
	void Initialize();

	// spriteを生成
	static Sprite* Create(Vector2 position);

	/// <summary>
	/// 座標の設定
	/// </summary>
	void SetPosition(const Vector2& position);

	const Vector2& GetPosition() const { return position_; }

	// 描画
	void Draw(ViewProjection v,uint32_t t);

private: // メンバ変数

	D3D12_VERTEX_BUFFER_VIEW sVBV_{};
	Resource sResource_ = {};
	Vector4 color_ = {};
	WorldTransform w_ = {};
	Vector2 position_ = {};

};
