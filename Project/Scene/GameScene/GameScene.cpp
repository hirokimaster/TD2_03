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
		enemy_->SetBehaviorRequest(Enemy::Behavior::kHit);
	}
	else if (player_->GetLeftAttack() && player_->GetLTimer() <= 1) {
		enemy_->SetEnemyHp(player_->GetPlayerPower());
		enemy_->SetBehaviorRequest(Enemy::Behavior::kHit);
	}

	camera_.UpdateMatrix();

	ImGui::Begin("Camera");

	float translate[3] = { camera_.translate.x,camera_.translate.y,camera_.translate.z };
	ImGui::DragFloat3("transform", translate, -20, 4);

	camera_.translate = { translate[0],translate[1],translate[2] };

	camera_.UpdateMatrix();

	ImGui::End();

}

// 描画						  
void GameScene::Draw(){
	enemy_->Draw(camera_);
	player_->Draw(camera_);

}