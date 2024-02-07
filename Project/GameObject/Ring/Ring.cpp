#include "Ring.h"

void Ring::Initialize()
{
	ringTex = texture_->Load("resources/ring.png");

	ringModel_.reset(Model::CreateObj("ring.obj"));
	ringModel_->SetTexHandle(ringTex);
	ringModel_->SetEnableLighting(true);

	ringWorldTransform.translate = ringPos;
	ringWorldTransform.rotate.y = 0.78f;
	ringWorldTransform.scale = { 10.0f, 10.0f, 10.0f };

	sekiTex = texture_->Load("resources/white.png");

	sekiModel_.reset(Model::CreateObj("seki.obj"));
	sekiModel_->SetTexHandle(sekiTex);
	sekiModel_->SetEnableLighting(true);

	sekiWorldTransform.translate = sekiPos;
	sekiWorldTransform.rotate.y = 0.78f;
	sekiWorldTransform.scale = { 10.0f, 10.0f, 10.0f };
}

void Ring::Update(PointLight pointLight)
{
	ringModel_->SetPointLightProperty(pointLight);
	sekiModel_->SetPointLightProperty(pointLight);

#ifdef _DEBUG
	ImGui::Begin("Ring pos");
	ImGui::DragFloat3("pos", &ringWorldTransform.translate.x, 0.01f, 10.0f);
	ImGui::End();

	ImGui::Begin("Seki pos");
	ImGui::DragFloat3("pos", &sekiWorldTransform.translate.x, 0.01f, 10.0f);
	ImGui::End();
#endif // _DEBUG


	ringWorldTransform.UpdateMatrix();
	sekiWorldTransform.UpdateMatrix();
}

void Ring::Draw(const Camera& camera)
{
	ringModel_->Draw(ringWorldTransform, camera, true);
	sekiModel_->Draw(sekiWorldTransform, camera, true);
}
