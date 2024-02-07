#include "GameOverScene.h"

void GameOverScene::Initialize()
{
	texHandleGameOver_ = TextureManager::Load("resources/Scene/gameover.png");
	texHandleA_ = TextureManager::Load("resources/Scene/A.png");
	texHandleReturn_ = TextureManager::Load("resources/Scene/return.png");
	spriteGameOver_.reset(Sprite::Create({ 0,0 }, { 1280.0f,720.0f }));
	spriteA_.reset(Sprite::Create({ 700.0f,500.0f }, { 32.0f,32.0f }));
	spriteReturn_.reset(Sprite::Create({ 450.0f,500.0f }, { 64.0f,32.0f }));
	spriteA_->SetScale({ 2.5f,2.5f });
	spriteReturn_->SetScale({ 2.5f,2.5f });
	startATimer_ = 0;
	Animation::GetInstance()->ModelDestruction();
	Animation::GetInstance()->InitfadeOut();
	Animation::GetInstance()->InitFadeIn();
	camera_.Initialize();

	overGongSound = Audio::GetInstance()->SoundLoadWave("resources/Sound/endGong.wav");
	Audio::GetInstance()->SoundPlayWave(overGongSound);
}

void GameOverScene::Update()
{
	++startATimer_;
	Animation::GetInstance()->FadeOut(true);
	
	if (Input::GetInstance()->GetJoystickState()) {

		if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
			isFadeIn_ = true;

		}
	}

	// シーンが切り替わる時にフェードインする
	if (isFadeIn_) {
		--sceneTimer_;
	}

	Animation::GetInstance()->FadeIn(isFadeIn_);

	if (sceneTimer_ <= 0.0f) {
		GameManager::GetInstance()->ChangeScene("TITLE");
	}

	camera_.UpdateMatrix();

#ifdef _DEBUG
	ImGui::Begin("Scene");
	ImGui::Text("titleScene push key 1");
	ImGui::End();
#endif // _DEBUG
}

void GameOverScene::Draw()
{
	spriteGameOver_->Draw(camera_, texHandleGameOver_);

	if (startATimer_ % 40 >= 20) {
		spriteA_->Draw(camera_, texHandleA_);
	}

	spriteReturn_->Draw(camera_, texHandleReturn_);

	Animation::GetInstance()->Draw(camera_);
}
