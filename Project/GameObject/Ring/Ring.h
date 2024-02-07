#pragma once
#include "Vector3.h"
#include "Model.h"
#include "TextureManager.h"

class Ring {
public:
	void Initialize();
	void Update(PointLight pointLight);
	void Draw(const Camera& camera);
private:
	TextureManager* texture_ = TextureManager::GetInstance();

	std::unique_ptr<Model> ringModel_;
	std::unique_ptr<Model> sekiModel_;

	WorldTransform ringWorldTransform;
	WorldTransform sekiWorldTransform;

	Vector3 ringPos{ 0.0f, -40.0f, 5.0f };
	Vector3 sekiPos{ 0.0f, -40.0f, 5.0f };

	uint32_t ringTex;
	uint32_t sekiTex;
};
