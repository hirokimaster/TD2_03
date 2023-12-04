#pragma once
#include "DirectXCommon.h"
#include "StringUtility.h"
#include "ShaderCompile.h"
#include "CreateResource.h"
#include "GraphicsPipeline.h"
#include "Matrix4x4.h"
#include "Mathfunction.h"
#include "WorldTransform.h"
#include "Camera/Camera.h"
#include "TextureManager.h"

class Triangle {
public:
	void Initialize();

	void Draw(WorldTransform worldTransform, Camera camera, uint32_t texHandle);

private:

	D3D12_VERTEX_BUFFER_VIEW VBV{};
	Resource resource_ = {};
	WorldTransform worldTransform_ = {};

};
