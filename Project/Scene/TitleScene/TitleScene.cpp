#include "TitleScene.h"

TitleScene::TitleScene(){}

TitleScene::~TitleScene(){}

void TitleScene::Initialize()
{
	texHandleTitle_ = TextureManager::Load("resources/title.png");
	spriteTitle_.reset(Sprite::Create({ 0,0 }, { 1280.0f,720.0f }));
	animation_ = std::make_unique<Animation>();
	animation_->InitFadeIn();
	camera_.Initialize();
}

void TitleScene::Update()
{

	XINPUT_STATE joyState{};
	XINPUT_VIBRATION vibration{}; 
	
	if (Input::GetInstance()->GetJoystickState(joyState)) {

		if (Input::GetInstance()->PressedButton(joyState, XINPUT_GAMEPAD_B)) {
			Input::GetInstance()->GamePadVibration(vibration, 32767,32767, 20);
		}
		
		if (Input::GetInstance()->PressedButton(joyState, XINPUT_GAMEPAD_A)) {
			GameManager::GetInstance()->ChangeScene("SELECT");
		}
	}

	if (Input::GetInstance()->PressedKey(DIK_1)) {

		isAnimation_ = true;
		//sceneNo_ = SELECT;

		//timerFlag_ = true;


	}

	// シーンが切り替わる時にフェードインする
	if (isAnimation_) {
		--sceneTimer_;
	}
	//animation_->FadeIn(isAnimation_);

	if (sceneTimer_ <= 0.0f) {
		GameManager::GetInstance()->ChangeScene("SELECT");
	}

	camera_.UpdateMatrix();
}

void TitleScene::Draw()
{
	spriteTitle_->Draw(camera_, texHandleTitle_);
	animation_->Draw(camera_);
}
