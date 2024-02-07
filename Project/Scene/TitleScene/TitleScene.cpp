#include "TitleScene.h"

TitleScene::TitleScene(){}

TitleScene::~TitleScene(){}

void TitleScene::Initialize()
{
	texHandleTitle_ = TextureManager::Load("resources/Scene/title.png");
	texHandleA_ = TextureManager::Load("resources/Scene/A.png");
	texHandleStart_ = TextureManager::Load("resources/Scene/Start.png");
	spriteTitle_.reset(Sprite::Create({ 0,0 }, { 1280.0f,720.0f }));
	spriteA_.reset(Sprite::Create({ 700.0f,500.0f }, { 32.0f,32.0f }));
	spriteStart_.reset(Sprite::Create({ 450.0f,500.0f }, { 64.0f,32.0f }));
	spriteA_->SetScale({ 2.5f,2.5f });
	spriteStart_->SetScale({ 2.5f,2.5f });
	Animation::GetInstance()->Initialize();
	Animation::GetInstance()->InitFadeIn();
	Animation::GetInstance()->InitfadeOut();
	startATimer_ = 0;
	camera_.Initialize();
}

void TitleScene::Update()
{
	++startATimer_;
	XINPUT_VIBRATION vibration{}; 
	
	if (Input::GetInstance()->GetJoystickState()) {

		if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_B)) {
			Input::GetInstance()->GamePadVibration(vibration, 32767,32767, 20);
		}
		
		if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
			isAnimation_ = true;
		}
	}

	// シーンが切り替わる時にフェードインする
	if (isAnimation_) {
		--sceneTimer_;
	}

	Animation::GetInstance()->FadeIn(isAnimation_);

	if (sceneTimer_ <= 0.0f) {
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
