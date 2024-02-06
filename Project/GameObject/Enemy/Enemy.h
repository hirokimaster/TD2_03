#pragma once
#include"Model.h"
#include"Sprite.h"
#include<optional>
#include<random>

class Enemy {
public:

	enum class Behavior
	{
		kRoot,		//待機
		kLeftAttack,	//左手攻撃
		kRightAttack,	//左手攻撃
		kRightHit,		//右手の攻撃に当たる
		kLeftHit,		//左手の攻撃に当たる
	};

	~Enemy();
	void Initialize(float hp);
	void Update(PointLight pointLight);
	void Draw(const Camera& camera);

	void InitializeFloatingGimmick();

	void UpAndDownMotion(float time);

	void SetEnemyHp(float hp);

	float GetEnemyHp() { return enemyHp; }

	void SetBehaviorRequest(Behavior behavior) { behaviorRequest_ = behavior; };

private:
	TextureManager* texture_ = TextureManager::GetInstance();

	float enemyHp;
	float HitTime = 60.0f;
	Vector2 drawScale;

	uint32_t enemyTex;
	uint32_t hpTex;
	uint32_t headTex;
	uint32_t headHitTex;;
	std::unique_ptr<Sprite> hpSprite_;

	std::unique_ptr<Model> headModel_;
	std::unique_ptr<Model> UpBodyModel_;
	std::unique_ptr<Model> NeckModel_;
	std::unique_ptr<Model> leftUpArmModel_;
	std::unique_ptr<Model> rightUpArmModel_;
	std::unique_ptr<Model> leftDownArmModel_;
	std::unique_ptr<Model> rightDownArmModel_;

	WorldTransform headWorldTransform;
	WorldTransform UpBodyWorldTransform;
	WorldTransform NeckWorldTransform;
	WorldTransform leftUpArmWorldTransform;
	WorldTransform rightUpArmWorldTransform;
	WorldTransform leftDownArmWorldTransform;
	WorldTransform rightDownArmWorldTransform;


	//浮遊ギミックの媒介変数
	float UpdownParameter_ = 0.0f;
	float swingParameter_ = 0.0f;
	float throwParameter_ = 0.0f;
	//浮遊移動のサイクル<frame>
	uint16_t cycle_ = 60;
	//浮遊の振動<m>
	float amplitude_ = 0.1f;
	float swing_ = 0.1f;
	float throw_ = 0.1f;
	bool isMove = false;


	//振る舞い
	Behavior behavior_ = Behavior::kRoot;
	std::optional<Behavior>behaviorRequest_ = std::nullopt;

	int MotionTimer_ = 0;
	int MotionCount_ = 0;

	bool isAttack_ = false;	//攻撃をするか
	float AttackTimer_ = 0;	//発生頻度

	int randomAttack;

private:

	
	void BehaviorRootUpdate();
	void BehaviorLeftAttackUpdate();
	void BehaviorRightAttackUpdate();
	void BehaviorLeftHitUpdate();
	void BehaviorRightHitUpdate();

	void BehaviorRootInitialize();	//待機
	void BehaviorLeftAttackInitialize();	//攻撃
	void BehaviorRightAttackInitialize();	//攻撃
	void BehaviorLeftHitInitialzie();	//攻撃に当たる
	void BehaviorRightHitInitialzie();	//攻撃に当たる
	
};