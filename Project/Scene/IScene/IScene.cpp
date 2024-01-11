#include "IScene.h"

IScene::~IScene() {}

int IScene::sceneNo_ = TITLE;

int IScene::GetSceneNo() { return sceneNo_; }