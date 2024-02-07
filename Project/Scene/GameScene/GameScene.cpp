#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	camera_.Initialize();
	camera_.translate.y = 1.0f;
	camera_.translate.z = -10.0f;
  
	//clickSound = Audio::GetInstance()->SoundLoadWave("resources/Sound/click.mp3");
	sceneBGM = Audio::GetInstance()->SoundLoadWave("resources/Sound/game.wav");
	Audio::GetInstance()->SoundPlayLoop(sceneBGM);
	hitSound = Audio::GetInstance()->SoundLoadWave("resources/Sound/hit.wav");
	enemyHitSound = Audio::GetInstance()->SoundLoadWave("resources/Sound/hit1.wav");
	clickSound = Audio::GetInstance()->SoundLoadWave("resources/Sound/gong.wav");
	Animation::GetInstance()->InitKO();
	Animation::GetInstance()->InitFadeIn();
	Animation::GetInstance()->InitfadeOut();

	

	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(4);
  
	camera_.rotate.x = 0.15f;

	enemy_ = std::make_unique<Enemy>();

	if (stageNo_ == EASY) {
		enemy_->Initialize(10.0f);
	}
	else if (stageNo_ == NORMAL) {
		enemy_->Initialize(100.0f);
	}
	else if (stageNo_ == HARD) {
		enemy_->Initialize(1000.0f);
	}
	

	player_ = std::make_unique<Player>();
	player_->Initialize();

	pointLight_.color = { 1.0f,0.4f,0.0f,1.0f };
	pointLight_.position = { 0.0f,30.0f,-0.5f };
	pointLight_.intensity = 0.3f;
	pointLight_.radius = 300.0f;
	pointLight_.decay = 1.5f;

	shakeTime = 0;


	ring_ = std::make_unique<Ring>();
	ring_->Initialize();

	texHandleUI_ = TextureManager::Load("resources/Scene/ui.png");
	texHandleHp_ = TextureManager::Load("resources/Scene/hp.png");
	spriteUI_.reset(Sprite::Create({ 480.0f,550.0f }, { 400.0f,300.0f }));
	spriteUI_->SetScale({ 0.8f,0.8f });

	for (uint32_t i = 0; i < 3; ++i) {
		spriteHp_[i].reset(Sprite::Create({ 10.0f + i * 40.0f, 100.0f}, { 31.0f,26.0f }));
	}

	isFadeIn_ = false;

	texHandleA_ = TextureManager::Load("resources/Scene/A.png");
	texHandleReturn_ = TextureManager::Load("resources/Scene/return.png");
	spriteA_.reset(Sprite::Create({ 700.0f,500.0f }, { 32.0f,32.0f }));
	spriteReturn_.reset(Sprite::Create({ 450.0f,500.0f }, { 64.0f,32.0f }));
	spriteA_->SetScale({ 2.5f,2.5f });
	spriteReturn_->SetScale({ 2.5f,2.5f });
	startATimer_ = 0;
	isKO_ = false;

}

// 更新
void GameScene::Update() {

	++startATimer_;
	Animation::GetInstance()->FadeOut(true);

	enemy_->Update(pointLight_);

	ring_->Update(pointLight_);

	player_->Update(pointLight_);

	if (player_->GetRightAttack() && player_->GetRTimer() <= 1) {
		enemy_->SetEnemyHp(static_cast<float>(player_->GetPlayerPower()));
		enemy_->SetBehaviorRequest(Enemy::Behavior::kRightHit);
		IsShake = true;
		player_->SetStamina();
		Audio::GetInstance()->SoundPlayWave(hitSound);
	}
	else if (player_->GetLeftAttack() && player_->GetLTimer() <= 1) {
		enemy_->SetEnemyHp(static_cast<float>(player_->GetPlayerPower()));
		enemy_->SetBehaviorRequest(Enemy::Behavior::kLeftHit);
		IsShake = true;
		player_->SetStamina();
		Audio::GetInstance()->SoundPlayWave(hitSound);
	}

	if (enemy_->GetisAttack() && enemy_->GetHitTimer() <= 1) {
		Audio::GetInstance()->SoundPlayWave(enemyHitSound);
		player_->SetPlayerHp();
	}

	// KO
	if (enemy_->GetEnemyHp() <= 0) {
		--koTimer_;
		Animation::GetInstance()->AnimationKO(camera_);
		Audio::GetInstance()->SoundPlayStop(sceneBGM);
		enemy_->SetBehaviorRequest(Enemy::Behavior::kRightHit);
	}

	if (koTimer_ <= 0.0f) {
		isKO_ = true;
	}

	if (isKO_ && Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
		Audio::GetInstance()->SoundPlayWave(clickSound);
		isFadeIn_ = true;
	}


	// playerのhpが0になったらGameOver
	if (player_->GetPlayerHp() <= 0) {

		//Animation::GetInstance()->AnimationKO(camera_);
		isFadeIn_ = true;
		Audio::GetInstance()->SoundPlayStop(sceneBGM);

	}

	// シーンが切り替わる時にフェードインする
	if (isFadeIn_) {
		--sceneTimer_;
	}

	Animation::GetInstance()->FadeIn(isFadeIn_);

	if (sceneTimer_ <= 0.0f && player_->GetPlayerHp() <= 0) {
		GameManager::GetInstance()->ChangeScene("GAMEOVER");
	}
	else if (sceneTimer_ <= 0.0f && isKO_) {
		GameManager::GetInstance()->ChangeScene("TITLE");
	}


#ifdef _DEBUG
	// ゲームオーバーにいくデバッグ用
	if (Input::GetInstance()->PressedKey(DIK_1)) {
		
	}

	ImGui::Begin("Light");
	ImGui::SliderFloat4("color", &pointLight_.color.x, 0.0f, 1.0f);
	ImGui::SliderFloat3("position", &pointLight_.position.x, -100.0f, 100.0f);
	ImGui::SliderFloat("intensity", &pointLight_.intensity, 0.0f, 10.0f);
	ImGui::SliderFloat("radius", &pointLight_.radius, 0.0f, 300.0f);
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

  	ring_->Draw(camera_);

	player_->Draw(camera_);

	spriteUI_->Draw(camera_, texHandleUI_);

	if (player_->GetPlayerHp() == 3) {
		for (int i = 0; i < 3; ++i) {
			spriteHp_[i]->Draw(camera_, texHandleHp_);
		}
	}
	else if (player_->GetPlayerHp() == 2) {
		for (int i = 0; i < 2; ++i) {
			spriteHp_[i]->Draw(camera_, texHandleHp_);
		}
	}
	else if (player_->GetPlayerHp() == 1) {
		for (int i = 0; i < 1; ++i) {
			spriteHp_[i]->Draw(camera_, texHandleHp_);
		}
	}
	else {
		for (int i = 0; i < 1; ++i) {
			spriteHp_[i].reset();
		}
	}

	if (isKO_) {

		spriteReturn_->Draw(camera_, texHandleReturn_);

		if (startATimer_ % 40 >= 20) {
			spriteA_->Draw(camera_, texHandleA_);
		}
	}

	Animation::GetInstance()->Draw(camera_);

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



