#include "Model.h"

Model* Model::model_;

Model::~Model()
{
	delete state_;
	delete model_;
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
	model_ = new Model;
	model_->Initialize(state);

	return model_;
}

void Model::Draw(WorldTransform worldTransform, ViewProjection viewprojection, uint32_t texHandle)
{
	
	state_->Draw(worldTransform, viewprojection, texHandle);
}
