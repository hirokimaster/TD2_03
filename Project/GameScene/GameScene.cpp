#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	model_ = Model::Create(new ModelSphere);

	t = TextureManager::Load("resources/uvChecker.png");
	w_.Initialize();
	v_.Initialize();
}

// 更新
void GameScene::Update() {

	w_.rotate.y += 0.03f;
	w_.UpdateMatrix();
	v_.UpdateMatrix();
	
}

// 描画
void GameScene::Draw(){
	model_->Draw(w_, v_, t);
}