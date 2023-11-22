#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	assert(model);

	model_ = model;
	worldTransform_.Initialize();
	
	// 初期座標をセット
	worldTransform_.translate = position;

}

// 更新
void PlayerBullet::Update() {
	// 行列を定数バッファに転送
	worldTransform_.UpdateMatrix();

}

// 描画
void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	// モデルの描画
	model_->Draw(worldTransform_, viewProjection);
}

void PlayerBullet::SetTexHandle(uint32_t texHandle)
{
	texHandle = texHandle_;
	model_->SetTexHandle(texHandle_);
}


