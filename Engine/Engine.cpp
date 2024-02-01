#include "Engine.h"

/// <summary>
/// 初期化
/// </summary>
void Engine::Initialize(){
	Framework::Initialize();
	// シーンの初期化
	gameManager_ = GameManager::GetInstance();
	gameManager_->SetNextScene(std::make_unique<TitleScene>());
	

}

void Engine::Update()
{
	Framework::Update();
}

void Engine::Draw()
{
	gameManager_->Draw();
}

/// <summary>
/// 終了
/// </summary>
void Engine::Finalize(){

	Framework::Finalize();
}
