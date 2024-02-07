#include "TitleScene.h"

TitleScene::TitleScene(){}

TitleScene::~TitleScene(){}

void TitleScene::Initialize()
{
	texHandleTitle_ = TextureManager::Load("resources/Scene/title.png");
	texHandleA_ = TextureManager::Load("resources/Scene/A.png");
	texHandleStart_ = TextureManager::Load("resources/Scene/Start.png");

	titleBGM = Audio::GetInstance()->SoundLoadWave("resources/Sound/title.wav");
	Audio::GetInstance()->SoundPlayLoop(titleBGM);
	clickSound = Audio::GetInstance()->SoundLoadWave("resources/Sound/gong.wav");

	spriteTitle_.reset(Sprite::Create({ 0,0 }, { 1280.0f,720.0f }));
	spriteA_.reset(Sprite::Create({ 700.0f,500.0f }, { 32.0f,32.0f }));
	spriteStart_.reset(Sprite::Create({ 450.0f,500.0f }, { 64.0f,32.0f }));
	spriteA_->SetScale({ 2.5f,2.5f });
	spriteStart_->SetScale({ 2.5f,2.5f });
	Animation::GetInstance()->Initialize();
	Animation::GetInstance()->InitFadeIn();
	startATimer_ = 0;
	camera_.Initialize();
}

void TitleScene::Update()
{
	

	++startATimer_;
	XINPUT_STATE joyState{};
	XINPUT_VIBRATION vibration{}; 
	
	if (Input::GetInstance()->GetJoystickState(joyState)) {

		if (Input::GetInstance()->PressedButton(joyState, XINPUT_GAMEPAD_B)) {
			Input::GetInstance()->GamePadVibration(vibration, 32767,32767, 20);
		}
		
		if (Input::GetInstance()->PressedButton(joyState, XINPUT_GAMEPAD_A)) {
			isAnimation_ = true;

			Audio::GetInstance()->SoundPlayWave(clickSound);
		

		}
	}

	// シーンが切り替わる時にフェードインする
	if (isAnimation_) {
		--sceneTimer_;
	}

	Animation::GetInstance()->FadeIn(isAnimation_);

	if (sceneTimer_ <= 0.0f) {
		Audio::GetInstance()->SoundPlayStop(titleBGM);
		GameManager::GetInstance()->ChangeScene("SELECT");

	}

	camera_.UpdateMatrix();
}

void TitleScene::Draw()
{
	spriteTitle_->Draw(camera_, texHandleTitle_);

	if (startATimer_ % 40 >= 20) {
		spriteA_->Draw(camera_, texHandleA_);
	}

	spriteStart_->Draw(camera_, texHandleStart_);

	Animation::GetInstance()->Draw(camera_);
}
