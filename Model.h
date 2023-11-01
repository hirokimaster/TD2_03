#pragma once
#include "ModelState.h"
#include "ModelSphere.h"
#include "Vector2.h"
#include <fstream>
#include <sstream>

struct MaterialData {
	std::string textureFilePath;
};

struct ModelData {
	std::vector<VertexData> vertices;
	MaterialData material;
};

class Model {
public:

	~Model();
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(ModelState* state);

	/// <summary>
	/// モデル生成
	/// </summary>
	/// <returns></returns>
	static Model* Create(ModelState* state);

	//static Model* CreateObj();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(WorldTransform worldTransform, ViewProjection viewprojection, uint32_t texHandle);

private:

	/// <summary>
	/// Objファイルを読む
	/// </summary>
	/// <param name="directoryPath"></param>
	/// <param name="filename"></param>
	/// <returns></returns>
	//static ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// mtlファイルを読む
	/// </summary>
	/// <param name="directoryPath"></param>
	/// <param name="filename"></param>
	/// <returns></returns>
	//static MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);

private: // メンバ変数

	ModelState* state_ = nullptr; // モデルのパターン
	static Model* model_;
};


