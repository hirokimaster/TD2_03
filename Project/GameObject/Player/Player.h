#pragma once
#include "Input.h"
#include "Vector3.h"
#include "Model.h"
#include "TextureManager.h"
#include "PlayerParticle.h"
const int TRIGGER_THRESHOLD = 30;

class Player {
public:
	~Player();

	void Initialize();
	void Update();
	void Draw(const Camera& camera);

	void RightAttack(XINPUT_STATE joyState);
	void LeftAttack(XINPUT_STATE joyState);

	void Gard(XINPUT_STATE joyState);

	/// <summary>
	/// hitParticle
	/// </summary>
	void AttackParticle();

	int GetPlayerPower() { return power; }

	bool GetRightAttack() { return isRightHit; }
	bool GetLeftAttack() { return isLeftHit; }

	uint32_t GetRTimer() { return Rtimer_; }
	uint32_t GetLTimer() { return Ltimer_; }

	Vector3 GetRightWorldPosition();
	Vector3 GetLeftWorldPosition();
	
private:
	Input* input_ = Input::GetInstance();
	TextureManager* texture_ = TextureManager::GetInstance();

	std::unique_ptr<Model> rightModel_;
	std::unique_ptr<Model> leftModel_;

	WorldTransform rightWorldTransform;
	WorldTransform leftWorldTransform;

	int power = 1;

	Vector3 rightHandPos{ 4.0f, -3.0f, 0.0f };
	Vector3 leftHandPos{ -4.0f, -3.0f, 0.0f };

	uint32_t playerTex;

	bool isRightHit;
	bool isLeftHit;

	uint32_t Ltimer_ = 0;
	uint32_t Rtimer_ = 0;

	/*-----------------------
		  hitParticle
	--------------------------*/
	std::list<std::unique_ptr<PlayerParticle>> rightAttackParticle_ = {};
	std::list<std::unique_ptr<PlayerParticle>> leftAttackParticle_ = {};
	std::list<std::unique_ptr<PlayerParticle>>::iterator rightParticleItr_;
	std::list<std::unique_ptr<PlayerParticle>>::iterator leftParticleItr_;
	bool isHitRAttack_;
	bool isHitLAttack_;

	float Rspeed = 0.001f;
	float Lspeed = 0.001f;

	float rotateSpeedX = 0.2f;
	float rotateSpeedY = 0.2f;
	float rotateSpeedZ = 0.4f;

	float rotateLSpeedX = 0.2f;
	float rotateLSpeedY = 0.2f;
	float rotateLSpeedZ = 0.4f;
};