#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	camera_.Initialize();
	camera_.translate.z = -10.0f;

	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(100);

	player_ = std::make_unique<Player>();
	player_->Initialize();
}

// 更新
void GameScene::Update() {
	enemy_->Update();

	player_->Update();


	if (player_->GetRightAttack() && player_->GetRTimer() <= 1) {
		enemy_->SetEnemyHp(player_->GetPlayerPower());
	}
	else if (player_->GetLeftAttack() && player_->GetLTimer() <= 1) {
		enemy_->SetEnemyHp(player_->GetPlayerPower());
	}

	camera_.UpdateMatrix();
}

// 描画						  
void GameScene::Draw(){
	enemy_->Draw();
	player_->Draw(camera_);
	player_->RightDraw(camera_);
	player_->LeftDraw(camera_);
}