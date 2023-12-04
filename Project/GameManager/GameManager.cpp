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

	sceneArr_[currentSceneNo_]->Update();
}

void GameManager::Initialize()
{
	// シーンのチェック
	prevSceneNo_ = currentSceneNo_;
	currentSceneNo_ = sceneArr_[currentSceneNo_]->GetSceneNo();
	sceneArr_[currentSceneNo_]->Initialize();
	// シ－ン変更のチェック
	if (prevSceneNo_ != currentSceneNo_) {
		sceneArr_[currentSceneNo_]->Initialize();

	}

}

void GameManager::Draw()
{
	sceneArr_[currentSceneNo_]->Draw();

}