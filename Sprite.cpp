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
	
	resource_.vertexResource = CreateResource::CreateBufferResource(sizeof(Vector4) * 3);

	VBV = CreateResource::CreateVertexBufferView(resource_.vertexResource, sizeof(Vector4));

	materialResource_ = Material::CreateMaterial(resource_.vertexResource);

	resource_.wvpResource = CreateResource::CreateBufferResource(sizeof(TransformationMatrix));
	
}


// 三角形描画
void Sprite::DrawTriangle(WorldTransform worldTransform){

	worldTransform.TransferMatrix(resource_.wvpResource);


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
	// wvp用のCBufferの場所を設定
	DirectXCommon::GetCommandList()->SetGraphicsRootConstantBufferView(1, resource_.wvpResource->GetGPUVirtualAddress());
	// 描画。(DrawCall/ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
	DirectXCommon::GetCommandList()->DrawInstanced(3, 1, 0, 0);

}
