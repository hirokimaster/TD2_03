#include "TitleScene.h"

void TitleScene::Initialize()
{
	texHandleTitle_ = TextureManager::Load("resources/title.png");
	spriteTitle_.reset(Sprite::Create({ 0,0 }, { 1280.0f,720.0f }));
	camera_.Initialize();
}

void TitleScene::Update()
{
	if (Input::GetInstance()->PressedKey(DIK_1)) {
		sceneNo_ = GAME;
	}

	camera_.UpdateMatrix();
}

void TitleScene::Draw()
{
	spriteTitle_->Draw(camera_, texHandleTitle_);
	ImGui::Begin("Scene");
	ImGui::Text("Game  1 ");
	ImGui::End();
}
