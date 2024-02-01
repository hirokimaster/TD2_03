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
	Gard(joyState);

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
	
	rightWorldTransform.translate.y += Rspeed;
	leftWorldTransform.translate.y += Lspeed;

	// プレイヤーふわふわ
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

	// 右拳のひねり
	if (rightWorldTransform.translate.z > 1.0f) {

		if (rightWorldTransform.rotate.x <= 0.7f) {
			rightWorldTransform.rotate.x += rotateSpeedX;
		}
		if (rightWorldTransform.rotate.y <= 0.25f) {
			rightWorldTransform.rotate.y += rotateSpeedY;
		}
		if (rightWorldTransform.rotate.z <= 1.5f) {
			rightWorldTransform.rotate.z += rotateSpeedZ;
		}
	}
	else if (rightWorldTransform.translate.z < 1.0f) {
		if (rightWorldTransform.rotate.x >= 0.0f) {
			rightWorldTransform.rotate.x -= rotateSpeedX;
		}
		if (rightWorldTransform.rotate.y >= 0.0f) {
			rightWorldTransform.rotate.y -= rotateSpeedY;
		}
		if (rightWorldTransform.rotate.z >= 0.0f) {
			rightWorldTransform.rotate.z -= rotateSpeedZ;
		}
	}

	// 左拳のひねり
	if (leftWorldTransform.translate.z > 1.0f) {

		if (leftWorldTransform.rotate.x <= 0.7f) {
			leftWorldTransform.rotate.x += rotateLSpeedX;
		}
		if (leftWorldTransform.rotate.y >= -0.25f) {
			leftWorldTransform.rotate.y -= rotateLSpeedY;
		}
		if (leftWorldTransform.rotate.z >= -1.5f) {
			leftWorldTransform.rotate.z -= rotateLSpeedZ;
		}
	}
	else if (leftWorldTransform.translate.z < 1.0f) {
		if (leftWorldTransform.rotate.x >= 0.0f) {
			leftWorldTransform.rotate.x -= rotateLSpeedX;
		}
		if (leftWorldTransform.rotate.y <= 0.0f) {
			leftWorldTransform.rotate.y += rotateLSpeedY;
		}
		if (leftWorldTransform.rotate.z <= 0.0f) {
			leftWorldTransform.rotate.z += rotateLSpeedZ;
		}
	}

	rightWorldTransform.UpdateMatrix();
	leftWorldTransform.UpdateMatrix();

#ifdef _DEBUG
	ImGui::Begin("Attack");
	ImGui::Text("RightAttack : %d", isLeftHit);
	ImGui::Text("LeftAttack : %d", isRightHit);
	ImGui::End();

	ImGui::Begin("rotate");
	ImGui::DragFloat3("R1ght", &rightWorldTransform.rotate.x, 0.01f, 10.0f);
	ImGui::DragFloat3("Left", &leftWorldTransform.rotate.x, 0.01f, 10.0f);
	ImGui::End();
#endif // _DEBUG
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

void Player::Gard(XINPUT_STATE joyState)
{
	if (input_->GetJoystickState(joyState)) {
		//rightWorldTransform.translate.x = (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 1.0f;
		//leftWorldTransform.translate.x = (float)joyState.Gamepad.sThumbLX / SHRT_MAX * 1.0f;
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

