#include "GameScene.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

}

// 初期化
void GameScene::Initialize() {
	camera_.Initialize();
	camera_.translate.z = -10.0f;

	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(4);

	player_ = std::make_unique<Player>();
	player_->Initialize();

	pointLight_.color = { 1.0f,1.0f,1.0f,1.0f };
	pointLight_.intensity = 0.0f;
	pointLight_.radius = 6.4f;
	pointLight_.decay = 1.2f;
	
	// クリア演出用のやつ
	spriteK_.reset(Sprite::Create({ 0,0 }, { 500.0f,500.0f }));
	spriteO_.reset(Sprite::Create({ 100.0f,0 }, { 500.0f,500.0f }));
	texHandleSpriteK_ = TextureManager::Load("resources/k.png");
	texHandleSpriteO_ = TextureManager::Load("resources/o.png");
	scaleK_ = { 0.1f,0.1f };
}

// 更新
void GameScene::Update() {
	enemy_->Update(pointLight_);

	player_->Update();

	if (player_->GetRightAttack() && player_->GetRTimer() <= 1) {
		enemy_->SetEnemyHp(player_->GetPlayerPower());
		enemy_->SetBehaviorRequest(Enemy::Behavior::kHit);
	}
	else if (player_->GetLeftAttack() && player_->GetLTimer() <= 1) {
		enemy_->SetEnemyHp(player_->GetPlayerPower());
		enemy_->SetBehaviorRequest(Enemy::Behavior::kHit);
	}

	/*-----------------------
		  クリア演出
	-------------------------*/
	if (isMoveK_) {
		++frameK_;
	}

	if (frameK_ >= endFrameK_) {
		isMoveK_ = false;
	}

	if (isMoveO_ && !isMoveK_) {
		++frameO_;
	}

	if (frameO_ >= endFrameO_) {
		isMoveO_ = false;
	}

	spriteK_->SetScale(scaleK_);
	scaleK_.x = 0.1f + (1.0f - 0.1f) * easeInSine(frameK_ / endFrameK_);
	scaleK_.y = 0.1f + (1.0f - 0.1f) * easeInSine(frameK_ / endFrameK_);

	spriteO_->SetScale(scaleO_);
	scaleO_.x = 0.1f + (1.0f - 0.1f) * easeInSine(frameO_ / endFrameO_);
	scaleO_.y = 0.1f + (1.0f - 0.1f) * easeInSine(frameO_ / endFrameO_);


#ifdef _DEBUG
	// ゲームオーバーにいくデバッグ用
	if (Input::GetInstance()->PressedKey(DIK_1)) {
		sceneNo_ = GAMEOVER;
	}

	ImGui::Begin("Light");
	ImGui::SliderFloat4("color", &pointLight_.color.x, 0.0f, 1.0f);
	ImGui::SliderFloat3("position", &pointLight_.position.x, -100.0f, 100.0f);
	ImGui::SliderFloat("intensity", &pointLight_.intensity, 0.0f, 10.0f);
	ImGui::SliderFloat("radius", &pointLight_.radius, 0.0f, 100.0f);
	ImGui::SliderFloat("decay", &pointLight_.decay, 0.0f, 10.0f);
	ImGui::End();

	if (Input::GetInstance()->PressedKey(DIK_P)) {
		isMoveK_ = true;
		isMoveO_ = true;
	}

#endif // _DEBUG

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
	spriteK_->Draw(camera_, texHandleSpriteK_);
	spriteO_->Draw(camera_, texHandleSpriteO_);
}