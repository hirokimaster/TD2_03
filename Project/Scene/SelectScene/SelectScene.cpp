#include "SelectScene.h"

SelectScene::SelectScene(){}

SelectScene::~SelectScene(){}

void SelectScene::Initialize()
{
	texHandleSelect_ = TextureManager::Load("resources/stageSelect.png");
	spriteSelect_.reset(Sprite::Create({ 0,0 }, { 1280.0f,720.0f }));
	selectNum_ = 1;
	animation_ = std::make_unique<Animation>();
	animation_->InitfadeOut();
	camera_.Initialize();
}

void SelectScene::Update()
{
	// フェードアウトさせる
	//isAnimation_ = true;
	animation_->FadeOut(isAnimation_);

	// ステージ番号選択
	if (Input::GetInstance()->PressedKey(DIK_RIGHT) && selectNum_ < 3) {
		selectNum_ += 1;
	}
	else if (Input::GetInstance()->PressedKey(DIK_LEFT) && selectNum_ > 1) {
		selectNum_ -= 1;
	}

	// 番号によってステージ変更
	if (Input::GetInstance()->PressedKey(DIK_RETURN) && selectNum_ == 1) {
		stageNo_ = EASY;
	}
	else if (Input::GetInstance()->PressedKey(DIK_RETURN) && selectNum_ == 2) {
		stageNo_ = NORMAL;
	}
	else if (Input::GetInstance()->PressedKey(DIK_RETURN) && selectNum_ == 3) {
		stageNo_ = HARD;
	}

	XINPUT_STATE joyState{};

	if (Input::GetInstance()->GetJoystickState(joyState)) {

		if (Input::GetInstance()->PressedButton(joyState, XINPUT_GAMEPAD_A)) {
			
		}
	}

	// ゲームシーンに切り替え
	if (Input::GetInstance()->PressedKey(DIK_RETURN)) {
		
	}

	camera_.UpdateMatrix();
}

void SelectScene::Draw()
{
	spriteSelect_->Draw(camera_, texHandleSelect_);
	animation_->Draw(camera_);

#ifdef _DEBUG
	ImGui::Begin("stageSlect");
	ImGui::Text("selectNum = %d", selectNum_);
	ImGui::End();
#endif // _DEBUG

}
