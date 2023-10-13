#include "Sprite.h"
#include "Vector4.h"

Sprite* Sprite::GetInstance() {
	static Sprite instance;
	return &instance;
}

/// <summary>
/// 初期化
/// </summary>
void Sprite::Initialize() {
	
	vertexResource_ = Resource::CreateBufferResource(sizeof(Vector4) * 3);

	VBV = Resource::CreateVertexBufferView(vertexResource_, sizeof(Vector4));

	// 頂点リソースにデータを書き込む
	Vector4* vertexData = nullptr;
	// 書き込むためのアドレスを取得
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	// 左下
	vertexData[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
	// 上
	vertexData[1] = { 0.0f, 0.5f, 0.0f, 1.0f };
	// 右下
	vertexData[2] = { 0.5f, -0.5f, 0.0f, 1.0f };

	materialResource_ = Resource::CreateBufferResource(sizeof(Vector4));
	// データを書き込む
	Vector4* materialData = nullptr;
	// アドレスを取得
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	// 赤
	*materialData = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

	
}


// 三角形描画
void Sprite::DrawTriangle(){

	Property property = GraphicsPipeline::GetInstance()->GetPs().triangle;

	// 三角形描画コマンド
	// Rootsignatureを設定。PSOに設定してるけど別途設定が必要
	DirectXCommon::GetCommandList()->SetGraphicsRootSignature(property.rootSignature_.Get());
	DirectXCommon::GetCommandList()->SetPipelineState(property.graphicsPipelineState_.Get()); // PSOを設定
	DirectXCommon::GetCommandList()->IASetVertexBuffers(0, 1, &VBV); // VBVを設定
	// 形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	DirectXCommon::GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// マテリアルCBufferの場所を設定
	DirectXCommon::GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());
	// 描画。(DrawCall/ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
	DirectXCommon::GetCommandList()->DrawInstanced(3, 1, 0, 0);

}
