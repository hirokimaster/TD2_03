#include "TitleScene.h"

TitleScene::TitleScene(){}

TitleScene::~TitleScene(){}

void TitleScene::Initialize()
{
	texHandleTitle_ = TextureManager::Load("resources/title.png");
	spriteTitle_.reset(Sprite::Create({ 0,0 }, { 1280.0f,720.0f }));
	animation_ = std::make_unique<Animation>();
	animation_->InitFadeIn();
	gameManager_ = GameManager::GetInstance();
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
			
		}
	}

	if (Input::GetInstance()->PressedKey(DIK_1)) {
		isAnimation_ = true;
		//sceneNo_ = SELECT;
	}

	// シーンが切り替わる時にフェードインする
	if (isAnimation_) {
		--sceneTimer_;
	}
	animation_->FadeIn(isAnimation_);

	if (sceneTimer_ <= 0.0f) {
		gameManager_->SetNextScene(std::make_unique<SelectScene>());
	}

	camera_.UpdateMatrix();
}

void TitleScene::Draw()
{
	spriteTitle_->Draw(camera_, texHandleTitle_);
	animation_->Draw(camera_);
}
