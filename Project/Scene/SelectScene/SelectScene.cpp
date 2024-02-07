#include "SelectScene.h"

SelectScene::SelectScene() {}

SelectScene::~SelectScene() {}

void SelectScene::Initialize()
{
	texHandleSelect1_ = TextureManager::Load("resources/Scene/stage1.png");
	texHandleSelect2_ = TextureManager::Load("resources/Scene/stage2.png");
	texHandleSelect3_ = TextureManager::Load("resources/Scene/stage3.png");
	texHandleS_ = TextureManager::Load("resources/Scene/select.png");
	spriteSelect_.reset(Sprite::Create({ 0,0 }, { 1280.0f,720.0f }));
	spriteS_.reset(Sprite::Create({ 40.0f,600.0f }, { 52.0f,32.0f }));
	spriteS_->SetScale({ 2.5f,2.5f });
	selectNum_ = 0;
	Animation::GetInstance()->InitfadeOut();
	Animation::GetInstance()->InitFadeIn();
	isFadeIn_ = false;
	camera_.Initialize();


	sceneBGM = Audio::GetInstance()->SoundLoadWave("resources/Sound/title.wav");
	Audio::GetInstance()->SoundPlayLoop(sceneBGM);
	clickSound = Audio::GetInstance()->SoundLoadWave("resources/Sound/gong.wav");

}

void SelectScene::Update()
{
	// フェードアウトさせる
	isAnimation_ = true;
	Animation::GetInstance()->FadeOut(isAnimation_);

	if (selectNum_ == 0) {
		texHandleSelect_ = texHandleSelect1_;
	}
	else if (selectNum_ == 1) {
		texHandleSelect_ = texHandleSelect2_;
	}
	else if (selectNum_ == 2) {
		texHandleSelect_ = texHandleSelect3_;
	}

	// ステージ番号選択
	if (Input::GetInstance()->PressedKey(DIK_RIGHT) && selectNum_ < 2) {
		selectNum_ += 1;
	}
	else if (Input::GetInstance()->PressedKey(DIK_LEFT) && selectNum_ > 0) {
		selectNum_ -= 1;
	}

	// 番号によってステージ変更
	if (Input::GetInstance()->PressedKey(DIK_RETURN) && selectNum_ == 0) {
		stageNo_ = EASY;
	}
	else if (Input::GetInstance()->PressedKey(DIK_RETURN) && selectNum_ == 1) {
		stageNo_ = NORMAL;
	}
	else if (Input::GetInstance()->PressedKey(DIK_RETURN) && selectNum_ == 2) {
		stageNo_ = HARD;
	}

	if (Input::GetInstance()->GetJoystickState()) {

		if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_DPAD_RIGHT) && selectNum_ < 2) {
			selectNum_ += 1;
		}
		else if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_DPAD_LEFT) && selectNum_ > 0) {
			selectNum_ -= 1;
		}


		if (Input::GetInstance()->PressedButton(XINPUT_GAMEPAD_A)) {
			isFadeIn_ = true;
			Audio::GetInstance()->SoundPlayStop(sceneBGM);
			Audio::GetInstance()->SoundPlayWave(clickSound);

		}

	

	// シーンが切り替わる時にフェードインする
	if (isFadeIn_) {
		--sceneTimer_;
	}


	Animation::GetInstance()->FadeIn(isFadeIn_);

	if (sceneTimer_ <= 0.0f) {
		GameManager::GetInstance()->ChangeScene("GAME");
	}


	camera_.UpdateMatrix();

}

void SelectScene::Draw()
{

	spriteSelect_->Draw(camera_, texHandleSelect_);
	spriteS_->Draw(camera_, texHandleS_);
	Animation::Draw(camera_);

#ifdef _DEBUG
	ImGui::Begin("stageSlect");
	ImGui::Text("selectNum = %d", selectNum_);
	ImGui::End();
#endif // _DEBUG

}
