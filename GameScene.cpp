#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {}

// 初期化
void GameScene::Initialize() {

	model = Model::Create(new ModelSphere);

	sprite = Sprite::Create({ 200.0f,100.0f });

	sprite2 = Sprite::Create({ 0,0 });
	
	viewProjection.Initialize();
	transform.Initialize();

}

// 更新
void GameScene::Update() {

	viewProjection.UpdateMatrix();
	transform.UpdateMatrix();
	transform.rotate.y += 0.03f;
}

// 描画
void GameScene::Draw(){

	// スプライト描画
	sprite->Draw(viewProjection, texHandle);
	sprite2->Draw(viewProjection, texHandle2);

	// 球の描画
	model->Draw(transform, viewProjection, texHandle);
}