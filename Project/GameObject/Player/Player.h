#pragma once
#include "Input.h"
#include "Vector3.h"
#include "Model.h"
#include "TextureManager.h"
#include "PlayerParticle.h"

class Player {
public:
	~Player();

	void Initialize();
	void Update(PointLight pointLight);
	void Draw(const Camera& camera);

	void RightAttack(XINPUT_STATE joyState);
	void LeftAttack(XINPUT_STATE joyState);

	void Gard(XINPUT_STATE joyState);

	/// <summary>
	/// hitParticle
	/// </summary>
	void AttackParticle();

	void SetStamina() { stamina -= 1; }
	void SetPlayerHp();

	int GetPlayerPower() { return power; }

	bool GetRightAttack() { return isRightHit; }
	bool GetLeftAttack() { return isLeftHit; }

	uint32_t GetRTimer() { return Rtimer_; }
	uint32_t GetLTimer() { return Ltimer_; }
	uint32_t GetPlayerHp() { return playerhp; }

	Vector3 GetRightWorldPosition();
	Vector3 GetLeftWorldPosition();
	
private:
	Input* input_ = Input::GetInstance();
	TextureManager* texture_ = TextureManager::GetInstance();

	std::unique_ptr<Model> rightModel_;
	std::unique_ptr<Model> leftModel_;

	WorldTransform rightWorldTransform;
	WorldTransform leftWorldTransform;

	// 初期位置
	Vector3 rightHandPos{ 4.0f, -3.0f, 0.0f };
	Vector3 leftHandPos{ -4.0f, -3.0f, 0.0f };

	uint32_t playerTex;

	// プレイヤー体力
	uint32_t playerhp = 3;

	//プレイヤー攻撃力
	uint32_t power = 1;

	// 攻撃判定
	bool isRightHit;
	bool isLeftHit;
	// 攻撃タイマー
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

	// 浮遊スピード
	float Rspeed = 0.001f;
	float Lspeed = 0.001f;

	// プレイヤーのスタミナ
	bool isStamina;
	uint32_t stamina = 300;
	uint32_t stTimer = 0;

	// ガード
	bool isGard;
};