#include "Player.h"

Player::~Player()
{
}

void Player::Initialize()
{
	playerTex = texture_->Load("resources/uvChecker.png");

	rightModel_.reset(Model::CreateObj("cube.obj"));
	rightModel_->SetTexHandle(playerTex);

	leftModel_.reset(Model::CreateObj("cube.obj"));
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

	rightWorldTransform.UpdateMatrix();
	leftWorldTransform.UpdateMatrix();

	ImGui::Begin("Attack");
	ImGui::Text("RightAttack : %d", isLeftHit);
	ImGui::Text("LeftAttack : %d", isRightHit);
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
