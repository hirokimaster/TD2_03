#include "GameOverScene.h"

void GameOverScene::Initialize()
{
	Animation::GetInstance()->ModelDestruction();
	texHandleGameOver_ = TextureManager::Load("resources/uvChecker.png");
	spriteGameOver_.reset(Sprite::Create({ 0,0 }, { 1280.0f,720.0f }));
	camera_.Initialize();
}

void GameOverScene::Update()
{

	XINPUT_STATE joyState{};

	if (Input::GetInstance()->GetJoystickState(joyState)) {

		if (Input::GetInstance()->PressedButton(joyState, XINPUT_GAMEPAD_A)) {
			GameManager::GetInstance()->ChangeScene("TITLE");
		}
	}

	if (Input::GetInstance()->PressedKey(DIK_1)) {
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
}
