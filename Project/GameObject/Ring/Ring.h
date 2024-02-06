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
	std::unique_ptr<Model> ringModel_;
	TextureManager* texture_ = TextureManager::GetInstance();

	WorldTransform ringWorldTransform;

	Vector3 ringPos{ 0.0f, -42.0f, 5.0f };

	uint32_t ringTex;
};
