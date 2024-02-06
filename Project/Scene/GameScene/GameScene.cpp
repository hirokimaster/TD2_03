#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	camera_.Initialize();
	camera_.translate.y = 1.0f;
	camera_.translate.z = -10.0f;
	camera_.rotate.x = 0.15f;

	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(100.0f);

	player_ = std::make_unique<Player>();
	player_->Initialize();


	shakeTime = 0;


	ring_ = std::make_unique<Ring>();
	ring_->Initialize();

}

// 更新
void GameScene::Update() {
	ring_->Update();

	enemy_->Update();

	player_->Update();

	if (player_->GetRightAttack() && player_->GetRTimer() <= 1) {
		enemy_->SetEnemyHp(static_cast<float>(player_->GetPlayerPower()));
		enemy_->SetBehaviorRequest(Enemy::Behavior::kHit);
		IsShake = true;
		player_->SetStamina();
	}
	else if (player_->GetLeftAttack() && player_->GetLTimer() <= 1) {
		enemy_->SetEnemyHp(static_cast<float>(player_->GetPlayerPower()));
		enemy_->SetBehaviorRequest(Enemy::Behavior::kHit);
		IsShake = true;
		player_->SetStamina();
	}

	camera_.UpdateMatrix();

	/*ImGui::Begin("Camera");

	float translate[3] = { camera_.translate.x,camera_.translate.y,camera_.translate.z };
	ImGui::DragFloat3("transform", translate, -20, 4);

	camera_.translate = { translate[0],translate[1],translate[2] };

	camera_.UpdateMatrix();

	ImGui::End();*/


	CameraShake();

}

// 描画						  
void GameScene::Draw(){
	enemy_->Draw(camera_);
	player_->Draw(camera_);
  	ring_->Draw(camera_);


}

void GameScene::CameraShake()
{

	if (shakeTime >= 15)
	{
		IsShake = false;
		shakeTime = 0;
		camera_.translate = { 0.0f,1.0f,-10.0f };

		camera_.rotate.x = 0.15f;
	}

	if (IsShake == true)
	{

		shakeTime++;
		std::random_device seedGenerator;
		std::mt19937 randomEngine(seedGenerator());
		std::uniform_real_distribution<float>distribution(-0.05f, 0.05f);

		camera_.translate.x = camera_.translate.x + distribution(randomEngine);
		camera_.translate.y = camera_.translate.y + distribution(randomEngine);

	}


}



