#pragma once
#include "Model/Model.h"

class PlayerBullet{
public:

	void Initialize(Model* model, const Vector3& position, uint32_t texHandle);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void GetTexHandle() { TexHandle_; }

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t TexHandle_ = 0;
};

