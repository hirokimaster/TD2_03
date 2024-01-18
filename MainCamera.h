#pragma once
#include "Camera.h"
#include "Vector3.h"
#include "WorldTransform.h"

class MainCamera {
public:
	void Initialize(Vector3 pos);
	void Update();

private:
	WorldTransform worldTransform_;

};