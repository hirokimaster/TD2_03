#include "WorldTransform.h"
#include "ViewProjection.h"

void WorldTransform::Initialize(){

	matWorld = MakeIdentityMatrix();

}

void WorldTransform::TransferMatrix(Microsoft::WRL::ComPtr<ID3D12Resource>& wvpResource, ViewProjection& viewProjection){

	TransformationMatrix* wvp = {};
	matWorld = Multiply(matWorld, Multiply(viewProjection.matView, viewProjection.matProjection));
	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvp));
	wvp->WVP = matWorld;

}

void WorldTransform::STransferMatrix(Microsoft::WRL::ComPtr<ID3D12Resource>& wvpResource, ViewProjection& viewProjection)
{
	TransformationMatrix* wvp = {};
	sMatWorld = Multiply(matWorld, Multiply(viewProjection.sMatView, viewProjection.sMatProjection));
	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvp));
	wvp->WVP = sMatWorld;
}

void WorldTransform::UpdateMatrix(){

	matWorld = MakeAffineMatrix(scale, rotate, translate);

	if (parent) {
		matWorld = Multiply(matWorld, parent->matWorld);
	}

}

