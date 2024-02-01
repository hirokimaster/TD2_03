#pragma once
#include "IScene/IScene.h"
#include <memory>

class GameManager{
public:
	
	static GameManager* GetInstance();

	void Update(); // ゲームループを呼び出す

	void Initialize(); // 初期化

	void Draw();

	void Finalize();

	void SetNextScene(std::unique_ptr<IScene> nextScene) { nextScene_ = std::move(nextScene); }

private:
	GameManager() = default;
	~GameManager() = default;
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	std::unique_ptr<IScene> scene_ = nullptr; // 今のシーン
	std::unique_ptr<IScene> nextScene_ = nullptr; // 次のシーン


};
