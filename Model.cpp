#include "Model.h"

Model::~Model()
{
	delete state_;
	delete model_;
}

Model* Model::GetInstance() {
	static Model instance;
	return &instance;
}

/// <summary>
/// 初期化
/// </summary>
void Model::Initialize(ModelState* state)
{
	state_ = state;
	state_->Initialize(this);

}

/// <summary>
/// モデル生成
/// </summary>
/// <returns></returns>
Model* Model::Create(ModelState* state)
{
	Model::GetInstance()->model_ = new Model;
	Model::GetInstance()->model_->Initialize(state);

	return Model::GetInstance()->model_	;
}

void Model::Draw(WorldTransform worldTransform, ViewProjection viewprojection, uint32_t texHandle)
{
	
	state_->Draw(worldTransform, viewprojection, texHandle);
}
