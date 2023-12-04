#pragma once
#include "WorldTransform.h"
#include "GraphicsPipeline.h"
#include "TextureManager.h"
#include "Camera/Camera.h"

class Model;

class IModelState {
public:
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="state"></param>
    virtual void Initialize(Model* state) = 0;


    /// <summary>
    /// 描画
    /// </summary>
    virtual void Draw(WorldTransform worldTransform, Camera camera, uint32_t texHandle) = 0;

};
