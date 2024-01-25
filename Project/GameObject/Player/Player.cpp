#include "Player.h"

Player::~Player()
{
}

void Player::Initialize()
{
	playerTex = texture_->Load("resources/uvChecker.png");

	rightModel_.reset(Model::CreateObj("rightHand.obj"));
	rightModel_->SetTexHandle(playerTex);

	leftModel_.reset(Model::CreateObj("leftHand.obj"));
	leftModel_->SetTexHandle(playerTex);

	rightWorldTransform.Initialize();
	leftWorldTransform.Initialize();

	rightWorldTransform.translate = rightHandPos;
	leftWorldTransform.translate = leftHandPos;
}

void Player::Update()
{

	XINPUT_STATE joyState{};

	RightAttack(joyState);
	LeftAttack(joyState);

	rightWorldTransform.translate.y += Rspeed;
	leftWorldTransform.translate.y += Lspeed;

	if (rightWorldTransform.translate.y <= -2.97f) {
		Rspeed *= -1;
	}
	if (rightWorldTransform.translate.y >= -3.03f) {
		Rspeed *= -1;
	}

	if (leftWorldTransform.translate.y <= -2.98f) {
		Lspeed *= -1;
	}
	if (leftWorldTransform.translate.y >= -3.04f) {
		Lspeed *= -1;
	}

	if (rightWorldTransform.translate.z > 0.5f) {
		rightWorldTransform.rotate.x += rotateSpeedX;
		rightWorldTransform.rotate.y += rotateSpeedY;
		rightWorldTransform.rotate.z += rotateSpeedZ;

		if (rightWorldTransform.rotate.x >= 0.7f) {
			rotateSpeedX = 0;
		}
		if (rightWorldTransform.rotate.y >= 0.25f) {
			rotateSpeedY = 0;
		}
		if (rightWorldTransform.rotate.z >= 1.5f) {
			rotateSpeedZ = 0;
		}
	}

	rightWorldTransform.UpdateMatrix();
	leftWorldTransform.UpdateMatrix();

	ImGui::Begin("Attack");
	ImGui::Text("RightAttack : %d", isLeftHit);
	ImGui::Text("LeftAttack : %d", isRightHit);
	ImGui::End();

	ImGui::Begin("rotate");
	ImGui::DragFloat3("R1ght", &rightWorldTransform.rotate.x, 0.01f, 10.0f);
	ImGui::DragFloat3("Left", &leftWorldTransform.rotate.x, 0.01f, 10.0f);
	ImGui::End();
}

void Player::RightAttack(XINPUT_STATE joyState)
{
	if (input_->GetJoystickState(joyState)) {

		rightWorldTransform.translate.z = (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 15.0f;

		if (rightWorldTransform.translate.z >= 15.0f) {
			++Rtimer_;
			isRightHit = true;
		}
		else {
			Rtimer_ = 0;
			isRightHit = false;
		}
	}
}

void Player::LeftAttack(XINPUT_STATE joyState)
{
	if (input_->GetJoystickState(joyState)) {
		leftWorldTransform.translate.z = (float)joyState.Gamepad.sThumbLY / SHRT_MAX * 15.0f;

		if (leftWorldTransform.translate.z >= 15.0f) {
			++Ltimer_;
			isLeftHit = true;
		}
		else {
			Ltimer_ = 0;
			isLeftHit = false;
		}
	}
}

void Player::RightDraw(const Camera& camera)
{
	rightModel_->Draw(rightWorldTransform, camera);
}

void Player::LeftDraw(const Camera& camera)
{
	leftModel_->Draw(leftWorldTransform, camera);
}
