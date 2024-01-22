#pragma once
#include"Model.h"

class Enemy {
public:
	~Enemy();
	void Initialize(int hp);
	void Update();
	void Draw(const Camera& camera);

	void InitializeFloatingGimmick();

	void UpAndDownMotion(float time);

	void SetEnemyHp(int hp) { enemyHp -= hp;}

	int GetEnemyHp() { return enemyHp; }

private:
	TextureManager* texture_ = TextureManager::GetInstance();

	int enemyHp;

	uint32_t enemyTex;

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
	WorldTransform leftDowmArmWorldTransform;
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

};