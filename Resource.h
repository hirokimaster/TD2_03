#pragma once
#include "DirectXCommon.h"
#include "Vector4.h"

// Resource作成
Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(Microsoft::WRL::ComPtr<ID3D12Device> device, size_t sizeInBytes);
// VBV
D3D12_VERTEX_BUFFER_VIEW CreateVertexBufferView(Microsoft::WRL::ComPtr<ID3D12Resource> resource, size_t sizeInBytes);

