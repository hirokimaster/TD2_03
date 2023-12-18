#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
}

// 初期化
void GameScene::Initialize() {
	camera_.Initialize();
	/*----------------------------
		 テクスチャ読み込み
	------------------------------*/
	texHandlePlayer_ = TextureManager::Load("resources/uvChecker.png");
	/*----------------------------
		      プレイヤー
	------------------------------*/
	modelPlayer_.reset(Model::CreateObj("cube.obj"));
	player_ = make_unique<Player>();
	player_->Initialize(modelPlayer_.get(), texHandlePlayer_);
}

// 更新
void GameScene::Update() {
	
	camera_.UpdateMatrix();
	player_->Update();

}

// 描画						  
void GameScene::Draw(){
	
	player_->Draw(camera_);

}