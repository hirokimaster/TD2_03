#pragma
#include "DirectXCommon.h"
#include "Vector4.h"
#include "CreateResource.h"

class Material {
public:
	
	static Microsoft::WRL::ComPtr<ID3D12Resource> CreateMaterial(Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource);

};
