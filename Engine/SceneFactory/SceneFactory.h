#pragma once
#include "AbstractSceneFactory.h"
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"
#include "SelectScene/SelectScene.h"

class SceneFactory : public AbstractSceneFactory {
public:
	/// <summary>
	/// シーン生成
	/// </summary>
	/// <param name="sceneName"></param>
	/// <returns></returns>
	std::unique_ptr<IScene> CreateScene(const std::string& sceneName)override;

};
