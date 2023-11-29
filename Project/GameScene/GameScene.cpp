#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	model_.reset(Model::CreateObj("cube.obj"));
	tex_ = TextureManager::Load("resources/monsterBall.png");
	tex2_ = TextureManager::Load("resources/monsterBall.png");
	model_->SetTexHandle(tex_);
	v_.Initialize();
	w_.Initialize();
}

// 更新
void GameScene::Update() {
	v_.UpdateMatrix();
	w_.UpdateMatrix();
}

// 描画						  
void GameScene::Draw(){
	model_->Draw(w_, v_);
}