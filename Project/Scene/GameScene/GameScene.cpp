#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	camera_.Initialize();
	sprite_ = std::make_unique<Sprite>();
	sprite_.reset(Sprite::Create({120.0f,0},{512.0f,512.0f}));
	tex_ = TextureManager::Load("resources/uvChecker.png");
}

// 更新
void GameScene::Update() {
	camera_.UpdateMatrix();
}

// 描画						  
void GameScene::Draw(){
	sprite_->Draw(camera_, tex_);
}