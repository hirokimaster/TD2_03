#include "IScene.h"

IScene::~IScene() {}

int IScene::sceneNo_ = GAME;

int IScene::GetSceneNo() { return sceneNo_; }