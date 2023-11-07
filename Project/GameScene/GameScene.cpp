#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	model_ = Model::CreateObj("axis.obj");
	texHandle_ = TextureManager::Load("uvChecker.png");
	viewProjection_.Initialize();
	worldTransform_.Initialize();
}

// 更新
void GameScene::Update() {
	viewProjection_.UpdateMatrix();
	worldTransform_.UpdateMatrix();
}

// 描画
void GameScene::Draw(){
	model_->DrawObj(worldTransform_, viewProjection_, texHandle_);
}