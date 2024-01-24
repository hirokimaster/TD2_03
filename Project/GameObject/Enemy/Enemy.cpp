#include "Enemy.h"
#include "imgui.h"

Enemy::~Enemy()
{
}

void Enemy::Initialize(int hp)
{
	enemyTex = texture_->Load("resources/uvChecker.png");

	enemyHp = hp;

	headModel_.reset(Model::CreateObj("enemy/Head.obj"));
	UpBodyModel_.reset(Model::CreateObj("enemy/Body.obj"));
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

	WaitMotion();

	InitializeFloatingGimmick();

}

void Enemy::Update()
{

	//BehaviorRootUpdate();
	//BehaviorAttackUpdate();
	
	
	if (behaviorRequest_)
	{
		//振る舞いを変更する
		behavior_ = behaviorRequest_.value();
		//各振る舞いごとの初期化を実行
		switch (behavior_)
		{
		case Enemy::Behavior::kRoot:
		default:

			break;
		case Enemy::Behavior::kAttack:
			break;
		}

		behaviorRequest_ = std::nullopt;
	}

	/*if (IsWaitMotion == true)
	{
		WaitMotion();
		UpAndDownMotion(1.5f);
	}

	if (IsHitMotion == true)
	{
		IsWaitMotion = false;
		
		HitTime--;
		RightHitMotion();

		if (HitTime <= 0)
		{
			IsHitMotion=false;
			IsWaitMotion = true;
			HitTime = 60.0f;
		}
	}*/

	headWorldTransform.UpdateMatrix();
	UpBodyWorldTransform.UpdateMatrix();
	NeckWorldTransform.UpdateMatrix();
	leftUpArmWorldTransform.UpdateMatrix();
	rightUpArmWorldTransform.UpdateMatrix();
	leftDowmArmWorldTransform.UpdateMatrix();
	rightDownArmWorldTransform.UpdateMatrix();



#ifdef _DEBUG



	ImGui::Begin("Enemy HP");
	ImGui::Text("%d", enemyHp);
	ImGui::Text("%f", HitTime);

	if (ImGui::TreeNode("BodyModel")) {
		float translate[3] = { UpBodyWorldTransform.translate.x,UpBodyWorldTransform.translate.y,UpBodyWorldTransform.translate.z };
		ImGui::DragFloat3("transform", translate, -20, 4);

		float rotate[3] = { UpBodyWorldTransform.rotate.x,UpBodyWorldTransform.rotate.y,UpBodyWorldTransform.rotate.z };
		ImGui::DragFloat3("rotate", rotate, -20, 4);

		UpBodyWorldTransform.translate = { translate[0],translate[1],translate[2] };
		UpBodyWorldTransform.rotate = { rotate[0],rotate[1],rotate[2] };

		UpBodyWorldTransform.UpdateMatrix();
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("HaadModel")) {
		float translate[3] = { headWorldTransform.translate.x,headWorldTransform.translate.y,headWorldTransform.translate.z };
		ImGui::DragFloat3("transform", translate, -20, 4);

		float rotate[3] = { headWorldTransform.rotate.x,headWorldTransform.rotate.y,headWorldTransform.rotate.z };
		ImGui::DragFloat3("rotate", rotate, -20, 4);

		headWorldTransform.translate = { translate[0],translate[1],translate[2] };
		headWorldTransform.rotate = { rotate[0],rotate[1],rotate[2] };

		headWorldTransform.UpdateMatrix();
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("NeckModel")) {
		float translate[3] = { NeckWorldTransform.translate.x,NeckWorldTransform.translate.y,NeckWorldTransform.translate.z };
		ImGui::DragFloat3("transform", translate, -20, 4);

		float rotate[3] = { NeckWorldTransform.rotate.x,NeckWorldTransform.rotate.y,NeckWorldTransform.rotate.z };
		ImGui::DragFloat3("rotate", rotate, -20, 4);

		NeckWorldTransform.translate = { translate[0],translate[1],translate[2] };
		NeckWorldTransform.rotate = { rotate[0],rotate[1],rotate[2] };

		NeckWorldTransform.UpdateMatrix();
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("leftUpModel")) {
		float translate[3] = { leftUpArmWorldTransform.translate.x,leftUpArmWorldTransform.translate.y,leftUpArmWorldTransform.translate.z };
		ImGui::DragFloat3("transform", translate, -20, 4);

		float rotate[3] = { leftUpArmWorldTransform.rotate.x,leftUpArmWorldTransform.rotate.y,leftUpArmWorldTransform.rotate.z };
		ImGui::DragFloat3("rotate", rotate, -20, 4);

		leftUpArmWorldTransform.translate = { translate[0],translate[1],translate[2] };
		leftUpArmWorldTransform.rotate = { rotate[0],rotate[1],rotate[2] };

		leftUpArmWorldTransform.UpdateMatrix();
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("rightUpModel")) {
		float translate[3] = { rightUpArmWorldTransform.translate.x,rightUpArmWorldTransform.translate.y,rightUpArmWorldTransform.translate.z };
		ImGui::DragFloat3("transform", translate, -20, 4);

		float rotate[3] = { rightUpArmWorldTransform.rotate.x,rightUpArmWorldTransform.rotate.y,rightUpArmWorldTransform.rotate.z };
		ImGui::DragFloat3("rotate", rotate, -20, 4);

		rightUpArmWorldTransform.translate = { translate[0],translate[1],translate[2] };
		rightUpArmWorldTransform.rotate = { rotate[0],rotate[1],rotate[2] };

		rightUpArmWorldTransform.UpdateMatrix();
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("leftDownModel")) {
		float translate[3] = { leftDowmArmWorldTransform.translate.x,leftDowmArmWorldTransform.translate.y,leftDowmArmWorldTransform.translate.z };
		ImGui::DragFloat3("transform", translate, -20, 4);

		float rotate[3] = { leftDowmArmWorldTransform.rotate.x,leftDowmArmWorldTransform.rotate.y,leftDowmArmWorldTransform.rotate.z };
		ImGui::DragFloat3("rotate", rotate, -20, 4);

		leftDowmArmWorldTransform.translate = { translate[0],translate[1],translate[2] };
		leftDowmArmWorldTransform.rotate = { rotate[0],rotate[1],rotate[2] };

		leftDowmArmWorldTransform.UpdateMatrix();
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("rightDownModel")) {
		float translate[3] = { rightDownArmWorldTransform.translate.x,rightDownArmWorldTransform.translate.y,rightDownArmWorldTransform.translate.z };
		ImGui::DragFloat3("transform", translate, -20, 4);

		float rotate[3] = { rightDownArmWorldTransform.rotate.x,rightDownArmWorldTransform.rotate.y,rightDownArmWorldTransform.rotate.z };
		ImGui::DragFloat3("rotate", rotate, -20, 4);

		rightDownArmWorldTransform.translate = { translate[0],translate[1],translate[2] };
		rightDownArmWorldTransform.rotate = { rotate[0],rotate[1],rotate[2] };

		rightDownArmWorldTransform.UpdateMatrix();
		ImGui::TreePop();
	}

	ImGui::End();
#endif // _DEBUG
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

void Enemy::BehaviorRootInitialize()
{

}

void Enemy::BehaviorAttackInitialize()
{

}

void Enemy::BehaviorRootUpdate()
{
	if (IsWaitMotion == true)
	{
		WaitMotion();
		UpAndDownMotion(1.5f);
	}
}

void Enemy::BehaviorAttackUpdate()
{
	AttackMotion();
	

}

void Enemy::RightHitMotion()
{
	UpBodyWorldTransform.translate = { 0.0f,-1.3f,-5.0f };
	UpBodyWorldTransform.rotate = { 0.0f,-0.2f,0.1f };

	NeckWorldTransform.translate = { -0.04f,0.0f,0.0f };
	NeckWorldTransform.rotate = { 0.0f,0.3f,0.0f };

	leftUpArmWorldTransform.translate = { -0.45f,0.25f,0.0f };
	leftUpArmWorldTransform.rotate = { 0.0f,0.0f,-0.5f };

	rightUpArmWorldTransform.translate = { -0.2f,0.0f,0.5f };
	rightUpArmWorldTransform.rotate = { 0.02f,-7.9f,0.0f };

	leftDowmArmWorldTransform.translate = { 0.9f,-0.23f,0.97f };
	leftDowmArmWorldTransform.rotate = { 0.0f,1.0f,0.58f };

	rightDownArmWorldTransform.translate = { -0.3f,-0.24f,0.09f };
	rightDownArmWorldTransform.rotate = { 0.05f,-0.1f,-0.3f };

}

void Enemy::LeftHitMotion()
{
	UpBodyWorldTransform.translate = { 0.0f,-1.3f,-5.0f };
	UpBodyWorldTransform.rotate = { 0.0f,-0.2f,0.1f };

	NeckWorldTransform.translate = { -0.04f,0.0f,0.0f };
	NeckWorldTransform.rotate = { 0.0f,0.3f,0.0f };

	leftUpArmWorldTransform.translate = { -0.45f,0.25f,0.0f };
	leftUpArmWorldTransform.rotate = { 0.0f,0.0f,-0.5f };

	rightUpArmWorldTransform.translate = { -0.2f,0.0f,0.5f };
	rightUpArmWorldTransform.rotate = { 0.02f,-7.9f,0.0f };

	leftDowmArmWorldTransform.translate = { 0.9f,-0.23f,0.97f };
	leftDowmArmWorldTransform.rotate = { 0.0f,1.0f,0.58f };

	rightDownArmWorldTransform.translate = { -0.3f,-0.24f,0.09f };
	rightDownArmWorldTransform.rotate = { 0.05f,-0.1f,-0.3f };

}

void Enemy::AttackMotion()
{
	UpBodyWorldTransform.translate = { 0.0f,-1.3f,-5.0f };
	UpBodyWorldTransform.rotate = { -0.1f,0.2f,0.0f };

	NeckWorldTransform.translate = { 0.0f,0.0f,0.0f };
	NeckWorldTransform.rotate = { 0.0f,-0.1f,0.0f };

	leftUpArmWorldTransform.translate = { 0.0f,0.07f,0.68f };
	leftUpArmWorldTransform.rotate = { -0.7f,-1.3f,-0.7f };

	rightUpArmWorldTransform.translate = { -0.1f,0.0f,0.5f };
	rightUpArmWorldTransform.rotate = { 0.678f,-7.8f,-0.7f };

	leftDowmArmWorldTransform.translate = { 0.0f,-0.0f,0.0f };
	leftDowmArmWorldTransform.rotate = { 0.0f,0.0f,0.0f };

	rightDownArmWorldTransform.translate = { -0.54f,-0.37f,0.35f };
	rightDownArmWorldTransform.rotate = { 0.0f,-0.35f,-0.5f };
}

void Enemy::WaitMotion()
{

	UpBodyWorldTransform.translate = { 0.0f,-0.7f,-5.0f };
	UpBodyWorldTransform.rotate = { 0.0f,-0.0f,0.0f };

	NeckWorldTransform.translate = { 0.0f,0.0f,0.0f };
	NeckWorldTransform.rotate = { 0.0f,0.0f,0.0f };

	leftUpArmWorldTransform.translate = { 0.2f,0.6f,0.1f };
	leftUpArmWorldTransform.rotate = { -0.0f,1.0f,-0.9f };

	rightUpArmWorldTransform.translate = { -0.2f,0.6f,0.0f };
	rightUpArmWorldTransform.rotate = { 0.0f,-1.0f,0.9f };

	leftDowmArmWorldTransform.translate = { 0.4f,-0.0f,0.0f };
	leftDowmArmWorldTransform.rotate = { 0.0f,1.0f,0.0f };

	rightDownArmWorldTransform.translate = { -0.4f,-0.01f,0.0f };
	rightDownArmWorldTransform.rotate = { 0.0f,-1.0f,-0.0f };

}

void Enemy::InitializeFloatingGimmick() {

	//浮遊ギミックの媒介変数
	UpdownParameter_ = 0.0f;
	swingParameter_ = 0.0f;
	//浮遊移動のサイクル<frame>
	uint16_t cycle_ = 60;
	//浮遊の振動<m>
	amplitude_ = 0.05f;
}

void Enemy::UpAndDownMotion(float time)
{
	//1フレームでのパラメータ加算値
	const float step = time * 3.14f / cycle_;
	//パラメータを１ステップ分加算
	UpdownParameter_ += step;
	//2πを超えたら０に戻す
	UpdownParameter_ = std::fmod(UpdownParameter_, 2.0f * 3.14f);
	//浮遊を座標に反映
	UpBodyWorldTransform.translate.y = -0.8f + (std::sin(UpdownParameter_) * amplitude_);
}

