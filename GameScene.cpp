#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {}

// 初期化
void GameScene::Initialize() {

	model = Model::Create(new ModelSphere);
	sprite = Sprite::Create({ 200.0f,100.0f });
	
	viewProjection.Initialize();
	transform.Initialize();

}

// 更新
void GameScene::Update() {
	
	transform.rotate.y += 200.0f;
	viewProjection.UpdateMatrix();
	transform.UpdateMatrix();
	
}

// 描画
void GameScene::Draw(){

	// スプライト描画
	sprite->Draw(viewProjection, texHandle);

	// 球の描画
	model->Draw(transform, viewProjection, texHandle2);
}