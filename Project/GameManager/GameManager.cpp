#include "GameManager.h"
#include "GameScene/GameScene.h"
#include "TitleScene/TitleScene.h"
#include "SelectScene/SelectScene.h"
#include  "GameOverScene/GameOverScene.h"

GameManager* GameManager::GetInstance()
{
	static GameManager instance;
	return &instance;
}

void GameManager::Update() {

	if (nextScene_) {
	
		scene_ = std::move(nextScene_);
		nextScene_ = nullptr;

		scene_->SetGameManager(this);

		scene_->Initialize();
	}

	scene_->Update();
}

void GameManager::Initialize()
{
	scene_->Initialize();
}

void GameManager::Draw()
{
	scene_->Draw();
}

void GameManager::Finalize()
{
	
}
