#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete modelPlayer_.get();
}

// 初期化
void GameScene::Initialize() {
	viewProjection_.Initialize();
	/*----------------------------
		 テクスチャ読み込み
	------------------------------*/
	texHandlePlayer_ = TextureManager::Load("resources/uvChecker.png");
	texHandlePlayerBullet_ = TextureManager::Load("resources/uvChecker.png");
	/*----------------------------
		      プレイヤー
	------------------------------*/
	modelPlayer_ = make_unique<Model>();
	modelPlayer_.reset(Model::CreateObj("cube.obj"));
	player_ = make_unique<Player>();
	player_->Initialize(modelPlayer_.get(), texHandlePlayer_);

}

// 更新
void GameScene::Update() {
	
	viewProjection_.UpdateMatrix();
	player_->Update();

}

// 描画
void GameScene::Draw(){
	
	player_->Draw(viewProjection_);

}