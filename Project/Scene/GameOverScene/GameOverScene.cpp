#include "GameOverScene.h"

void GameOverScene::Initialize()
{
	texHandleGameOver_ = TextureManager::Load("resources/Clear.png");
	spriteGameOver_.reset(Sprite::Create({ 0,0 }, { 1280.0f,720.0f }));
	camera_.Initialize();
}

void GameOverScene::Update()
{
	camera_.UpdateMatrix();
}

void GameOverScene::Draw()
{
	spriteGameOver_->Draw(camera_, texHandleGameOver_);
}
