#include "TitleScene.h"

TitleScene::TitleScene(){}

TitleScene::~TitleScene(){}

void TitleScene::Initialize()
{
	texHandleTitle_ = TextureManager::Load("resources/title.png");
	texHandleBlack_ = TextureManager::Load("resources/black.png");
	spriteTitle_.reset(Sprite::Create({ 0,0 }, { 1280.0f,720.0f }));
	spriteBlack_.reset(Sprite::Create({ 0,0 }, { 1280.0f,720.0f },{1.0f,1.0f,1.0f,0.0f}));
	camera_.Initialize();
}

void TitleScene::Update()
{

	XINPUT_STATE joyState{};
	XINPUT_VIBRATION vibration{}; 

	//// ゲームパッド未接続なら何もせず抜ける
	//if (!Input::GetInstance()->GetJoystickState(joyState)) {
	//	return;
	//}
	
	if (Input::GetInstance()->GetJoystickState(joyState)) {

		if (Input::GetInstance()->PressedButton(joyState, XINPUT_GAMEPAD_B)) {
			Input::GetInstance()->GamePadVibration(vibration, 32767,32767, 20);
		}
		
		if (Input::GetInstance()->PressedButton(joyState, XINPUT_GAMEPAD_A)) {
			sceneNo_ = SELECT;
		}
	}

	if (Input::GetInstance()->PressedKey(DIK_1)) {
		//timerFlag_ = true;
		sceneNo_ = GAME;
	}

	if (timerFlag_) {
		sceneTimer_++;

		if (sceneTimer_ >= 10) {
			color_.w += 0.008f;
			spriteBlack_->SetColor({ color_ });
		}
	}

	if (color_.w >= 1.2f) {
		sceneNo_ = SELECT;

	}

	camera_.UpdateMatrix();
}

void TitleScene::Draw()
{
	spriteTitle_->Draw(camera_, texHandleTitle_);
	spriteBlack_->Draw(camera_, texHandleBlack_);

#ifdef _DEBUG
	ImGui::Begin("Scene");
	ImGui::Text("Game  1 ");
	ImGui::Text("timer = %d", sceneTimer_);
	ImGui::End();
#endif 
}
