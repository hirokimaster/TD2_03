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

	rightAttackParticle_ = std::make_unique<PlayerParticle>();
	rightAttackParticle_->Initialize();
	leftAttackParticle_ = std::make_unique<PlayerParticle>();
	leftAttackParticle_->Initialize();

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

	rightAttackParticle_->Update();
	leftAttackParticle_->Update();

	ImGui::Begin("Attack");
	ImGui::Text("RightAttack : %d", isLeftHit);
	ImGui::Text("LeftAttack : %d", isRightHit);
	ImGui::End();
}

void Player::Draw(const Camera& camera)
{
	rightModel_->Draw(rightWorldTransform, camera);
	leftModel_->Draw(leftWorldTransform, camera);

	if (isRightHit) {
		rightAttackParticle_->Draw(camera);
	}
	else if (isLeftHit) {
		leftAttackParticle_->Draw(camera);
	}
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

Vector3 Player::GetRightWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = rightWorldTransform.matWorld.m[3][0];
	worldPos.y = rightWorldTransform.matWorld.m[3][1];
	worldPos.z = rightWorldTransform.matWorld.m[3][2];

	return worldPos;
}

Vector3 Player::GetLeftWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = leftWorldTransform.matWorld.m[3][0];
	worldPos.y = leftWorldTransform.matWorld.m[3][1];
	worldPos.z = leftWorldTransform.matWorld.m[3][2];

	return worldPos;
}
