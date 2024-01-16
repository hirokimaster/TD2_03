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
	
	if (Input::GetInstance()->PressedKey(DIK_1)) {
		timerFlag_ = true;
	}

	if (timerFlag_) {
		sceneTimer_++;

		if (sceneTimer_ >= 10) {
			color_.w += 0.008f;
			spriteBlack_->SetColor({ color_ });
		}
	}

	if (color_.w >= 1.2f) {
		sceneNo_ = GAME;

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
