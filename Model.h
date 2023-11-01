#pragma once
#include "ModelState.h"
#include "ModelSphere.h"

class Model {
public:

	~Model();
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(ModelState* state);

	/// <summary>
	/// モデル生成
	/// </summary>
	/// <returns></returns>
	static Model* Create(ModelState* state);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(WorldTransform worldTransform, ViewProjection viewprojection, uint32_t texHandle);

private:

	ModelState* state_ = nullptr; // モデルのパターン
	static Model* model_;
};


