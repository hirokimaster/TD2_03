#include "ViewProjection.h"

void ViewProjection::Initialize(){

	matView = MakeIdentityMatrix();
	matProjection = MakeIdentityMatrix();
}

void ViewProjection::UpdateMatrix(){

	matView = Inverse(MakeAffineMatrix(scale, rotate, translate));
	matProjection = MakePerspectiveFovMatrix(fov, aspectRatio, nearZ, farZ);

}
