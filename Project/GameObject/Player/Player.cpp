#include "Player.h"

Player::~Player()
{
}

void Player::Initialize()
{
	playerTex = texture_->Load("resources/red.png");

	rightModel_.reset(Model::CreateObj("rightHand.obj"));
	rightModel_->SetTexHandle(playerTex);

	leftModel_.reset(Model::CreateObj("leftHand.obj"));
	leftModel_->SetTexHandle(playerTex);

	rightModel_->SetEnableLighting(true);
	leftModel_->SetEnableLighting(true);

	rightWorldTransform.Initialize();
	leftWorldTransform.Initialize();

	rightWorldTransform.translate = rightHandPos;
	leftWorldTransform.translate = leftHandPos;

	isStamina = true;
	isGard = false;
}

void Player::Update(PointLight pointLight)
{

	XINPUT_STATE joyState{};

	if (isStamina) {
		RightAttack(joyState);
		LeftAttack(joyState);
	}

	
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

	// プレイヤーのスタミナ
	if (stamina <= 0) {
		isStamina = false;
		rightAttackParticle_.clear();
		leftAttackParticle_.clear();
		stTimer++;
		rightWorldTransform.translate.z = rightHandPos.z;
		leftWorldTransform.translate.z = leftHandPos.z;
	}
	if (stTimer == 300) {
		stamina = 25;
		stTimer = 0;
		isStamina = true;
	}
	
	rightWorldTransform.translate.y += Rspeed;
	leftWorldTransform.translate.y += Lspeed;

	// プレイヤーふわふわ
	{
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
	}

	// 右拳のひねり
	{
		if (rightWorldTransform.translate.z > 1.0f) {

			rightWorldTransform.rotate.x = 0.9f;
			rightWorldTransform.rotate.y = 0.4f;
			rightWorldTransform.rotate.z = 1.8f;
		}

		if (rightWorldTransform.translate.z < 1.0f && rightWorldTransform.translate.z > 0.8f) {

			rightWorldTransform.rotate.x = 0.7f;
			rightWorldTransform.rotate.y = 0.4f;
			rightWorldTransform.rotate.z = 1.6f;
		}

		if (rightWorldTransform.translate.z < 0.8f && rightWorldTransform.translate.z > 0.5f) {

			rightWorldTransform.rotate.x = 0.3f;
			rightWorldTransform.rotate.y = 0.4f;
			rightWorldTransform.rotate.z = 0.8f;
		}

		if (rightWorldTransform.translate.z < 0.5f) {

			rightWorldTransform.rotate.x = 0.0f;
			rightWorldTransform.rotate.y = 0.0f;
			rightWorldTransform.rotate.z = 0.0f;
		}
	}

	// 左拳のひねり
	{
		if (leftWorldTransform.translate.z > 1.0f) {

			leftWorldTransform.rotate.x = 0.9f;
			leftWorldTransform.rotate.y = -0.4f;
			leftWorldTransform.rotate.z = -1.8f;
		}

		if (leftWorldTransform.translate.z < 1.0f && leftWorldTransform.translate.z > 0.8f) {

			leftWorldTransform.rotate.x = 0.7f;
			leftWorldTransform.rotate.y = -0.4f;
			leftWorldTransform.rotate.z = -1.6f;
		}

		if (leftWorldTransform.translate.z < 0.8f && leftWorldTransform.translate.z > 0.5f) {

			leftWorldTransform.rotate.x = 0.3f;
			leftWorldTransform.rotate.y = -0.4f;
			leftWorldTransform.rotate.z = -0.8f;
		}

		if (leftWorldTransform.translate.z < 0.5f) {

			leftWorldTransform.rotate.x = 0.0f;
			leftWorldTransform.rotate.y = 0.0f;
			leftWorldTransform.rotate.z = 0.0f;
		}
	}

	// ガード
	{
		if (rightWorldTransform.translate.x <= 1.0f && leftWorldTransform.translate.x >= -1.0f) {

			rightWorldTransform.rotate.x = -0.1f;
			rightWorldTransform.rotate.y = -1.08f;
			rightWorldTransform.rotate.z = -0.6f;

			leftWorldTransform.rotate.x = 0.0f;
			leftWorldTransform.rotate.y = 0.98f;
			leftWorldTransform.rotate.z = 0.7f;

			isGard = true;
		}
		else {

			isGard = false;

		}
	}

	rightWorldTransform.UpdateMatrix();
	leftWorldTransform.UpdateMatrix();

	rightModel_->SetPointLightProperty(pointLight);
	leftModel_->SetPointLightProperty(pointLight);
  
#ifdef _DEBUG
  ImGui::Begin("Attack");
	ImGui::Text("RightAttack : %d", isRightHit);
	ImGui::Text("LeftAttack : %d", isLeftHit);

	ImGui::Text("stamina : %d", stamina);

	ImGui::DragFloat3("R1ght", &rightWorldTransform.rotate.x, 0.01f, 10.0f);
	ImGui::DragFloat3("Left", &leftWorldTransform.rotate.x, 0.01f, 10.0f);

	ImGui::Text("Gard : %d", isGard);

	ImGui::Text("HP : %d", playerhp);

	ImGui::End();
#endif // _DEBUG
}

void Player::Draw(const Camera& camera)
{
	rightModel_->Draw(rightWorldTransform, camera, true);
	leftModel_->Draw(leftWorldTransform, camera, true);

	for (rightParticleItr_ = rightAttackParticle_.begin(); rightParticleItr_ != rightAttackParticle_.end(); ++rightParticleItr_) {
		(*rightParticleItr_)->Draw(camera);
	}
	
	for (leftParticleItr_ = leftAttackParticle_.begin(); leftParticleItr_ != leftAttackParticle_.end(); ++leftParticleItr_) {
		(*leftParticleItr_)->Draw(camera);
	}
	

}

void Player::RightAttack(XINPUT_STATE joyState)
{
rightWorldTransform.translate.x = rightHandPos.x;

	if (input_->GetJoystickState(joyState)) {

		rightWorldTransform.translate.z = (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 10.0f;

		if (rightWorldTransform.translate.z >= 10.0f) {
			++Rtimer_;
			isRightHit = true;
			isHitRAttack_ = true;
			//joyState.Gamepad.bRightTrigger = 31;
		}
		else {
			Rtimer_ = 0;
			isRightHit = false;
			isHitRAttack_ = false;
		}
	}
}

void Player::LeftAttack(XINPUT_STATE joyState)
{
	leftWorldTransform.translate.x = leftHandPos.x;

	if (input_->GetJoystickState(joyState)) {
		leftWorldTransform.translate.z = (float)joyState.Gamepad.sThumbLY / SHRT_MAX * 10.0f;

		if (leftWorldTransform.translate.z >= 10.0f) {
			++Ltimer_;
			isLeftHit = true;
			isHitLAttack_ = true;
		}

		else {
			Ltimer_ = 0;
			isLeftHit = false;
			isHitLAttack_ = false;
		}

	}
}		  

void Player::Gard(XINPUT_STATE joyState)
{

	if (input_->GetJoystickState(joyState)) {
		rightWorldTransform.translate.x = 4.0f + (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 3.0f;
		leftWorldTransform.translate.x = -4.0f + (float)joyState.Gamepad.sThumbLX / SHRT_MAX * 3.0f;
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

void Player::SetPlayerHp()
{
	if (isGard == false) {
		playerhp -= 1;
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

