#pragma once
#include <memory>

enum SCENE { TITLE,SELECT,GAME,GAMEOVER };

enum STAGE { EASY, NORMAL, HARD };

class IScene
{
protected:
	// シーンナンバー
	static int sceneNo_;
	// ステージナンバー
	static int stageNo_;

public:

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual ~IScene();

	int GetSceneNo();

};
