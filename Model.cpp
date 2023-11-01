#include "Model.h"

Model* Model::model_;

Model::~Model()
{
	delete state_;
	delete model_;
}

/// <summary>
/// 初期化
/// </summary>
void Model::Initialize(ModelState* state)
{
	state_ = state;
	state_->Initialize(this);

}

/// <summary>
/// モデル生成
/// </summary>
/// <returns></returns>
Model* Model::Create(ModelState* state)
{
	model_ = new Model;
	model_->Initialize(state);

	return model_;
}

void Model::Draw(WorldTransform worldTransform, ViewProjection viewprojection, uint32_t texHandle)
{
	
	state_->Draw(worldTransform, viewprojection, texHandle);
}

//ModelData Model::LoadObjFile(const std::string& directoryPath, const std::string& filename)
//{
//	// 必要な変数を宣言
//	ModelData modelData; // 構築するModelData
//	std::vector<Vector4> positions; // 位置
//	std::vector<Vector3> normals; // 法線
//	std::vector<Vector2> texcoords; // テクスチャ座標
//	std::string line; // ファイルから読んだ1行を格納するもの
//	// ファイルを開く
//	std::ifstream file(directoryPath + "/" + filename); // ファイルを開く
//	assert(file.is_open()); // 開けなかったら止める
//	// ファイルを読む
//	while (std::getline(file, line)) {
//		std::string identifier;
//		std::istringstream s(line);
//		s >> identifier; // 先頭の識別子を読む
//
//		// identifierに応じた処理
//		if (identifier == "v") {
//			Vector4 position;
//			s >> position.x >> position.y >> position.z;
//			position.x *= -1.0f;
//			position.w = 1.0f;
//			positions.push_back(position);
//		}
//		else if (identifier == "vt") {
//			Vector2 texcoord;
//			s >> texcoord.x >> texcoord.y;
//			texcoord.y = 1.0f - texcoord.y;
//			texcoords.push_back(texcoord);
//		}
//		else if (identifier == "vn") {
//			Vector3 normal;
//			s >> normal.x >> normal.y >> normal.z;
//			normal.x *= -1.0f;
//			normals.push_back(normal);
//		}
//		else if (identifier == "f") {
//			VertexData triangle[3];
//			// 面は三角形限定。その他は未対応
//			for (int32_t faceVertex = 0; faceVertex < 3; ++faceVertex) {
//				std::string vertexDefinition;
//				s >> vertexDefinition;
//				// 頂点の要素へのindexは「位置/UV/法線」で格納されているので、分解してindexを取得する
//				std::istringstream v(vertexDefinition);
//				uint32_t elementIndices[3];
//				for (int32_t element = 0; element < 3; ++element) {
//					std::string index;
//					std::getline(v, index, '/'); // 区切りでインデックスを読んでいく
//					elementIndices[element] = std::stoi(index);
//				}
//				// 要素へのindexから、実際の要素の値を取得して、頂点を構築する
//				Vector4 position = positions[elementIndices[0] - 1];
//				Vector2 texcoord = texcoords[elementIndices[1] - 1];
//				Vector3 normal = normals[elementIndices[2] - 1];
//				triangle[faceVertex] = { position, texcoord, normal };
//			}
//			// 逆順で頂点を登録する
//			modelData.vertices.push_back(triangle[2]);
//			modelData.vertices.push_back(triangle[1]);
//			modelData.vertices.push_back(triangle[0]);
//		}
//		else if (identifier == "mtllib") {
//			// materialTemplateLibraryファイルの名前を取得する
//			std::string materialFilename;
//			s >> materialFilename;
//			// 基本的にobjファイルと同一階層にmtlは存在させるので、ディレクトリ名を渡す
//			modelData.material = LoadMaterialTemplateFile(directoryPath, materialFilename);
//		}
//	}
//
//	return modelData;
//}
//
//
