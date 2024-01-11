#include "GameManager.h"
#include "GameScene/GameScene.h"


GameManager::GameManager() {
	// 各シーンの配列
	sceneArr_[GAME] = std::make_unique<GameScene>();

	// 初期シーン
	currentSceneNo_ = GAME;

}

GameManager::~GameManager() {}

void GameManager::Run() {

	// シーンのチェック
	prevSceneNo_ = currentSceneNo_;
	currentSceneNo_ = sceneArr_[currentSceneNo_]->GetSceneNo();

	// シ－ン変更のチェック
	if (prevSceneNo_ != currentSceneNo_) {
		sceneArr_[currentSceneNo_]->Initialize();

	}

	sceneArr_[currentSceneNo_]->Update();
}

void GameManager::Initialize()
{
	sceneArr_[currentSceneNo_]->Initialize();
}

void GameManager::Draw()
{
	sceneArr_[currentSceneNo_]->Draw();

}