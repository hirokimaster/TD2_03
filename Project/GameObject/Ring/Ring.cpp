#include "Ring.h"

void Ring::Initialize()
{
	ringTex = texture_->Load("resources/uvChecker.png");

	ringModel_.reset(Model::CreateObj("ring.obj"));
	ringModel_->SetTexHandle(ringTex);

	ringWorldTransform.translate = ringPos;
	ringWorldTransform.rotate.y += 0.78f;
	ringWorldTransform.scale = { 10.0f, 10.0f, 10.0f };
}

void Ring::Update()
{
#ifdef _DEBUG
	ImGui::Begin("Ring pos");
	ImGui::DragFloat3("pos", &ringWorldTransform.translate.x, 0.01f, 10.0f);
	ImGui::End();
#endif // _DEBUG

	ringWorldTransform.UpdateMatrix();
}

void Ring::Draw(const Camera& camera)
{
	ringModel_->Draw(ringWorldTransform, camera);
}
