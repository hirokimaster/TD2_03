#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	camera_.Initialize();
	camera_.translate.y = 1.0f;
	camera_.translate.z = -10.0f;
  
	animation_ = std::make_unique<Animation>();
	animation_->InitKO();

	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(4);
  
	camera_.rotate.x = 0.15f;

	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(100.0f);

	player_ = std::make_unique<Player>();
	player_->Initialize();

	pointLight_.color = { 1.0f,1.0f,1.0f,1.0f };
	pointLight_.intensity = 0.0f;
	pointLight_.radius = 6.4f;
	pointLight_.decay = 1.2f;

	shakeTime = 0;


	ring_ = std::make_unique<Ring>();
	ring_->Initialize();

}

// 更新
void GameScene::Update() {

	enemy_->Update(pointLight_);

	ring_->Update();


	player_->Update();

	if (player_->GetRightAttack() && player_->GetRTimer() <= 1) {
		enemy_->SetEnemyHp(static_cast<float>(player_->GetPlayerPower()));
		enemy_->SetBehaviorRequest(Enemy::Behavior::kRightHit);
		IsShake = true;
		player_->SetStamina();
	}
	else if (player_->GetLeftAttack() && player_->GetLTimer() <= 1) {
		enemy_->SetEnemyHp(static_cast<float>(player_->GetPlayerPower()));
		enemy_->SetBehaviorRequest(Enemy::Behavior::kLeftHit);
		IsShake = true;
		player_->SetStamina();
	}

	if (enemy_->GetisAttack() && enemy_->GetHitTimer() <= 1) {
		player_->SetPlayerHp();
	}


	// 演出系
	animation_->AnimationKO(camera_);

#ifdef _DEBUG
	// ゲームオーバーにいくデバッグ用
	if (Input::GetInstance()->PressedKey(DIK_1)) {
		
	}

	ImGui::Begin("Light");
	ImGui::SliderFloat4("color", &pointLight_.color.x, 0.0f, 1.0f);
	ImGui::SliderFloat3("position", &pointLight_.position.x, -100.0f, 100.0f);
	ImGui::SliderFloat("intensity", &pointLight_.intensity, 0.0f, 10.0f);
	ImGui::SliderFloat("radius", &pointLight_.radius, 0.0f, 100.0f);
	ImGui::SliderFloat("decay", &pointLight_.decay, 0.0f, 10.0f);
	ImGui::End();


#endif // _DEBUG

	camera_.UpdateMatrix();

	
#ifdef _DEBUG
	ImGui::Begin("Camera");
  
	float translate[3] = { camera_.translate.x,camera_.translate.y,camera_.translate.z };
	ImGui::DragFloat3("transform", translate, -20, 4);

	camera_.translate = { translate[0],translate[1],translate[2] };

	camera_.UpdateMatrix();

	ImGui::End();

#endif // _DEBUG



	CameraShake();

}

// 描画						  
void GameScene::Draw(){
	enemy_->Draw(camera_);
	player_->Draw(camera_);

	animation_->Draw(camera_);

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



