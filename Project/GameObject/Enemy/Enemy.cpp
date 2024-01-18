#include "Enemy.h"
#include "imgui.h"

Enemy::~Enemy()
{
}

void Enemy::Initialize(int hp)
{
	enemyTex = texture_->Load("resources/uvChecker.png");

	enemyHp = hp;

	headModel_.reset(Model::CreateObj("enemy/head.obj"));
	UpBodyModel_.reset(Model::CreateObj("enemy/UpBody.obj"));
	NeckModel_.reset(Model::CreateObj("enemy/Neck.obj"));
	leftUpArmModel_.reset(Model::CreateObj("enemy/LeftUpArm.obj"));
	rightUpArmModel_.reset(Model::CreateObj("enemy/RightUpArm.obj"));
	leftDownArmModel_.reset(Model::CreateObj("enemy/LeftDownArm.obj"));
	rightDownArmModel_.reset(Model::CreateObj("enemy/RightDownArm.obj"));

	headModel_->SetTexHandle(enemyTex);
	UpBodyModel_->SetTexHandle(enemyTex);
	NeckModel_->SetTexHandle(enemyTex);
	leftUpArmModel_->SetTexHandle(enemyTex);
	rightUpArmModel_->SetTexHandle(enemyTex);
	leftDownArmModel_->SetTexHandle(enemyTex);
	rightDownArmModel_->SetTexHandle(enemyTex);


	headWorldTransform.Initialize();
	UpBodyWorldTransform.Initialize();
	NeckWorldTransform.Initialize();
	leftUpArmWorldTransform.Initialize();
	rightUpArmWorldTransform.Initialize();
	leftDowmArmWorldTransform.Initialize();
	rightDownArmWorldTransform.Initialize();


	//親子関係
	headWorldTransform.parent = &NeckWorldTransform;
	NeckWorldTransform.parent = &UpBodyWorldTransform;
	leftUpArmWorldTransform.parent = &UpBodyWorldTransform;
	rightUpArmWorldTransform.parent = &UpBodyWorldTransform;
	leftDowmArmWorldTransform.parent = &leftUpArmWorldTransform;
	rightDownArmWorldTransform.parent = &rightUpArmWorldTransform;

	UpBodyWorldTransform.scale= { 2.0f,2.0f,2.0f };
	UpBodyWorldTransform.translate = { 0.0f,-6.5f,0.0f };

	
}

void Enemy::Update()
{
	headWorldTransform.UpdateMatrix();
	UpBodyWorldTransform.UpdateMatrix();
	NeckWorldTransform.UpdateMatrix();
	leftUpArmWorldTransform.UpdateMatrix();
	rightUpArmWorldTransform.UpdateMatrix();
	leftDowmArmWorldTransform.UpdateMatrix();
	rightDownArmWorldTransform.UpdateMatrix();


	ImGui::Begin("Enemy HP");
	ImGui::Text("%d", enemyHp);

	float translate[3] = { UpBodyWorldTransform.translate.x,UpBodyWorldTransform.translate.y,UpBodyWorldTransform.translate.z };
	ImGui::SliderFloat3("transform", translate, -20, 4);

	UpBodyWorldTransform.translate = { translate[0],translate[1],translate[2] };

	UpBodyWorldTransform.UpdateMatrix();

	ImGui::End();
}

void Enemy::Draw(const Camera& camera)
{
	headModel_->Draw(headWorldTransform, camera);
	UpBodyModel_->Draw(UpBodyWorldTransform, camera);
	NeckModel_->Draw(NeckWorldTransform, camera);
	leftUpArmModel_->Draw(leftUpArmWorldTransform, camera);
	rightUpArmModel_->Draw(rightUpArmWorldTransform, camera);
	leftDownArmModel_->Draw(leftDowmArmWorldTransform, camera);
	rightDownArmModel_->Draw(rightDownArmWorldTransform, camera);
}
