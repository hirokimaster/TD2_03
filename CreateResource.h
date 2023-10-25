#pragma once
#include "DirectXCommon.h"
#include "Vector4.h"

struct Resource {
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource;

};

struct VertexData {
	Vector4 position;
};

class CreateResource {
public:
	// Resource作成
	static Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);
	// VBV
	static D3D12_VERTEX_BUFFER_VIEW CreateVertexBufferView(Microsoft::WRL::ComPtr<ID3D12Resource> resource, size_t sizeInBytes, int size);

};
