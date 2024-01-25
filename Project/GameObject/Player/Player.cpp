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

	/*-----------------------------
			hitParticle
	-------------------------------*/
	AttackParticle();

	for (rightParticleItr_ = rightAttackParticle_.begin(); rightParticleItr_ != rightAttackParticle_.end(); ++rightParticleItr_) {
		(*rightParticleItr_)->Update();
	}

	for (leftParticleItr_ = leftAttackParticle_.begin(); leftParticleItr_ != leftAttackParticle_.end(); ++leftParticleItr_) {
		(*leftParticleItr_)->Update();
	}	

	rightAttackParticle_.remove_if([](std::unique_ptr<PlayerParticle>& rightParticle) {
		if (rightParticle->IsDead()) {
			return true;
		}
		return false;
		});

	leftAttackParticle_.remove_if([](std::unique_ptr<PlayerParticle>& leftParticle) {
		if (leftParticle->IsDead()) {
			return true;
		}
		return false;
		});

	///	ここまで
	
	rightWorldTransform.UpdateMatrix();
	leftWorldTransform.UpdateMatrix();

	ImGui::Begin("Attack");
	ImGui::Text("RightAttack : %d", isLeftHit);
	ImGui::Text("LeftAttack : %d", isRightHit);
	ImGui::End();
}

void Player::Draw(const Camera& camera)
{
	rightModel_->Draw(rightWorldTransform, camera);
	leftModel_->Draw(leftWorldTransform, camera);

	for (rightParticleItr_ = rightAttackParticle_.begin(); rightParticleItr_ != rightAttackParticle_.end(); ++rightParticleItr_) {
		(*rightParticleItr_)->Draw(camera);
	}
	
	for (leftParticleItr_ = leftAttackParticle_.begin(); leftParticleItr_ != leftAttackParticle_.end(); ++leftParticleItr_) {
		(*leftParticleItr_)->Draw(camera);
	}
	

}

void Player::RightAttack(XINPUT_STATE joyState)
{
	if (input_->GetJoystickState(joyState)) {

		rightWorldTransform.translate.z = (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 15.0f;

		if (rightWorldTransform.translate.z >= 15.0f) {
			++Rtimer_;
			isRightHit = true;
			joyState.Gamepad.bRightTrigger = 31;
		}
		else {
			Rtimer_ = 0;
			isRightHit = false;
		}

		if (joyState.Gamepad.bRightTrigger > TRIGGER_THRESHOLD && !isHitRAttack_) {
			isHitRAttack_ = true;
			joyState.Gamepad.bRightTrigger = 0;
		}
		else {
			isHitRAttack_ = false;
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
			joyState.Gamepad.bLeftTrigger = 31;
		}
		else {
			Ltimer_ = 0;
			isLeftHit = false;
		}

		if (joyState.Gamepad.bLeftTrigger > TRIGGER_THRESHOLD && !isHitLAttack_) {
			isHitLAttack_ = true;
			joyState.Gamepad.bLeftTrigger = 0;
		}
		else {
			isHitLAttack_ = false;
		}
	}
}

/// <summary>
/// hitParticle
/// </summary>
void Player::AttackParticle()
{
	if (isHitRAttack_) {
		std::unique_ptr<PlayerParticle> rightParticle = std::make_unique<PlayerParticle>();
		rightParticle->RightInitialize({ rightWorldTransform.translate.x, rightWorldTransform.translate.y, 15.0f });
		rightAttackParticle_.push_back(std::move(rightParticle));
	}

	if (isHitLAttack_) {
		std::unique_ptr<PlayerParticle> leftParticle = std::make_unique<PlayerParticle>();
		leftParticle->LeftInitialize({ leftWorldTransform.translate.x, leftWorldTransform.translate.y, 15.0f });
		leftAttackParticle_.push_back(std::move(leftParticle));
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

