#include "Enemy.h"
#include "imgui.h"

Enemy::~Enemy()
{
}

void Enemy::Initialize(float hp)
{
	enemyTex = texture_->Load("resources/enemy/white.png");
	hpTex = texture_->Load("resources/enemy/red.png");
	headTex = texture_->Load("resources/enemy/head.png");
	headHitTex = texture_->Load("resources/enemy/headHit.png");

	enemyHp = hp;

	headModel_.reset(Model::CreateObj("enemy/Head.obj"));
	UpBodyModel_.reset(Model::CreateObj("enemy/Body.obj"));
	NeckModel_.reset(Model::CreateObj("enemy/Neck.obj"));
	leftUpArmModel_.reset(Model::CreateObj("enemy/LeftUpArm.obj"));
	rightUpArmModel_.reset(Model::CreateObj("enemy/RightUpArm.obj"));
	leftDownArmModel_.reset(Model::CreateObj("enemy/LeftDownArm.obj"));
	rightDownArmModel_.reset(Model::CreateObj("enemy/RightDownArm.obj"));

	headModel_->SetEnableLighting(true);
	UpBodyModel_->SetEnableLighting(true);
	NeckModel_->SetEnableLighting(true);
	leftUpArmModel_->SetEnableLighting(true);
	rightUpArmModel_->SetEnableLighting(true);
	leftDownArmModel_->SetEnableLighting(true);
	rightDownArmModel_->SetEnableLighting(true);

	headModel_->SetTexHandle(enemyTex);

  	headModel_->SetTexHandle(headTex);
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
	leftDownArmWorldTransform.Initialize();
	rightDownArmWorldTransform.Initialize();


	//親子関係
	headWorldTransform.parent = &NeckWorldTransform;
	NeckWorldTransform.parent = &UpBodyWorldTransform;
	leftUpArmWorldTransform.parent = &UpBodyWorldTransform;
	rightUpArmWorldTransform.parent = &UpBodyWorldTransform;
	leftDownArmWorldTransform.parent = &leftUpArmWorldTransform;
	rightDownArmWorldTransform.parent = &rightUpArmWorldTransform;


	BehaviorRootInitialize();

	hpSprite_.reset(Sprite::Create({ 0,0, }, { 10,10 }));
	drawScale = { 130.0f,3.0f };

	std::srand(static_cast<unsigned int>(std::time(0)));

	isAttack_ = false;
}

void Enemy::Update(PointLight pointLight)
{
	hpSprite_->SetScale(drawScale);


	if (behaviorRequest_)
	{
		//振る舞いを変更する
		behavior_ = behaviorRequest_.value();
		//各振る舞いごとの初期化を実行
		switch (behavior_)
		{
		case Enemy::Behavior::kRoot:
		default:
			//待機モーション
			BehaviorRootInitialize();
			break;
		case Enemy::Behavior::kLeftAttack:
			//左手の攻撃
			BehaviorLeftAttackInitialize();
			break;
		case Enemy::Behavior::kRightAttack:
			//右手の攻撃
			BehaviorRightAttackInitialize();
			break;
		case Enemy::Behavior::kRightHit:
			//右手の攻撃が当たったとき
			BehaviorRightHitInitialzie();
			break;
		case Enemy::Behavior::kLeftHit:
			//右手の攻撃が当たったとき
			BehaviorRightHitInitialzie();
			break;
		}

		behaviorRequest_ = std::nullopt;
	}

	switch (behavior_)
	{
	case Enemy::Behavior::kRoot:
	default:
		BehaviorRootUpdate();
		break;
	case Enemy::Behavior::kLeftAttack:
		BehaviorLeftAttackUpdate();
		break;
	case Enemy::Behavior::kRightAttack:
		BehaviorRightAttackUpdate();
		break;
	case Enemy::Behavior::kRightHit:
		BehaviorRightHitUpdate();
		break;
	case Enemy::Behavior::kLeftHit:
		BehaviorLeftHitUpdate();
		break;
	}

	if (isAttack_) {
		HitTimer_++;
	}
	else if (isAttack_ == false) {
		HitTimer_ = 0;
	}

	headModel_->SetPointLightProperty(pointLight);
	UpBodyModel_->SetPointLightProperty(pointLight);
	NeckModel_->SetPointLightProperty(pointLight);
	leftUpArmModel_->SetPointLightProperty(pointLight);
	rightUpArmModel_->SetPointLightProperty(pointLight);
	leftDownArmModel_->SetPointLightProperty(pointLight);
	rightDownArmModel_->SetPointLightProperty(pointLight);

	headWorldTransform.UpdateMatrix();
	UpBodyWorldTransform.UpdateMatrix();
	NeckWorldTransform.UpdateMatrix();
	leftUpArmWorldTransform.UpdateMatrix();
	rightUpArmWorldTransform.UpdateMatrix();
	leftDownArmWorldTransform.UpdateMatrix();
	rightDownArmWorldTransform.UpdateMatrix();


#ifdef _DEBUG



	ImGui::Begin("Enemy HP");
	ImGui::Text("%f", enemyHp);
	ImGui::Text("%f", HitTime);
	ImGui::Text("%f", AttackTimer_);
	ImGui::Text("%f", drawScale.x);
	ImGui::Text("%d", isAttack_);

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
		float translate[3] = { leftDownArmWorldTransform.translate.x,leftDownArmWorldTransform.translate.y,leftDownArmWorldTransform.translate.z };
		ImGui::DragFloat3("transform", translate, -20, 4);

		float rotate[3] = { leftDownArmWorldTransform.rotate.x,leftDownArmWorldTransform.rotate.y,leftDownArmWorldTransform.rotate.z };
		ImGui::DragFloat3("rotate", rotate, -20, 4);

		leftDownArmWorldTransform.translate = { translate[0],translate[1],translate[2] };
		leftDownArmWorldTransform.rotate = { rotate[0],rotate[1],rotate[2] };

		leftDownArmWorldTransform.UpdateMatrix();
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


	headModel_->Draw(headWorldTransform, camera, true);
	UpBodyModel_->Draw(UpBodyWorldTransform, camera, true);
	/*NeckModel_->Draw(NeckWorldTransform, camera);*/
	leftUpArmModel_->Draw(leftUpArmWorldTransform, camera, true);
	rightUpArmModel_->Draw(rightUpArmWorldTransform, camera, true);
	leftDownArmModel_->Draw(leftDownArmWorldTransform, camera, true);
	rightDownArmModel_->Draw(rightDownArmWorldTransform, camera, true);

	hpSprite_->Draw(camera, hpTex);
}


void Enemy::BehaviorRootUpdate()
{
	UpAndDownMotion(1.5f);

	AttackTimer_--;


	if (AttackTimer_ <= 0)
	{
		if (randomAttack == 0) {
			behaviorRequest_ = Behavior::kLeftAttack;
		}
		else {
			behaviorRequest_ = Behavior::kRightAttack;
		}
	}
}


void Enemy::BehaviorLeftAttackUpdate()
{
	MotionTimer_++;

	//振りかぶり
	if (MotionCount_ == 0)
	{
		if (MotionTimer_ == 10)
		{
			MotionCount_ = 1;
		}

		UpBodyWorldTransform.rotate.y -= 0.02f;

		leftUpArmWorldTransform.translate.x += 0.02f;
		leftUpArmWorldTransform.translate.y -= 0.018f;
		leftUpArmWorldTransform.translate.z -= 0.01f;

		leftUpArmWorldTransform.rotate.y -= 0.18f;
		leftUpArmWorldTransform.rotate.z += 0.09f;

		leftDownArmWorldTransform.translate.z += 0.03f;
		leftDownArmWorldTransform.rotate.y += 0.16f;
	}



	//攻撃
	if (MotionCount_ == 1)
	{
		if (MotionTimer_ == 30)
		{
			MotionCount_ = 2;
		}

		UpBodyWorldTransform.rotate.y += 0.06f / 2.0f;

		NeckWorldTransform.rotate.x -= 0.01f / 2.0f;
		NeckWorldTransform.rotate.y -= 0.01f / 2.0f;

		leftUpArmWorldTransform.translate.x -= 0.02f / 2.0f;
		leftUpArmWorldTransform.translate.y += 0.008f / 2.0f;
		leftUpArmWorldTransform.translate.z += 0.01f / 2.0f;

		leftUpArmWorldTransform.rotate.y += 0.21f / 2.0f;
	

		leftDownArmWorldTransform.translate.z -= 0.03f / 2.0f;
		leftDownArmWorldTransform.rotate.y -= 0.26f / 2.0f;

	}

	//硬直
	if (MotionCount_ == 2)
	{
		isAttack_ = true;

		if (MotionTimer_ == 50)
		{
			MotionCount_ = 3;
			isAttack_ = false;
		}
	}

	//躰を戻す
	if (MotionCount_ == 3)
	{
		if (MotionTimer_ == 60)
		{
			MotionCount_ = 4;
		}
		UpBodyWorldTransform.rotate.y -= 0.06f / 1.0f;

		NeckWorldTransform.rotate.x += 0.01f / 1.0f;
		NeckWorldTransform.rotate.y += 0.01f / 1.0f;

		leftUpArmWorldTransform.translate.x += 0.02f / 1.0f;
		leftUpArmWorldTransform.translate.y -= 0.008f / 1.0f;
		leftUpArmWorldTransform.translate.z -= 0.01f / 1.0f;

		leftUpArmWorldTransform.rotate.y -= 0.21f / 1.0f;


		leftDownArmWorldTransform.translate.z += 0.03f / 1.0f;
		leftDownArmWorldTransform.rotate.y += 0.26f / 1.0f;
	}

	if (MotionCount_ == 4)
	{
		behaviorRequest_ = Behavior::kRoot;
	}
}

void Enemy::BehaviorRightAttackUpdate()
{
	MotionTimer_++;

	//振りかぶり
	if (MotionCount_ == 0)
	{
		if (MotionTimer_ == 10)
		{
			MotionCount_ = 1;
		}

		UpBodyWorldTransform.rotate.y += 0.02f;

		/*rightUpArmWorldTransform.translate.x -= 0.02f;*/
		rightUpArmWorldTransform.translate.y -= 0.018f;
		/*rightUpArmWorldTransform.translate.z += 0.01f;*/

		rightUpArmWorldTransform.rotate.y += 0.02f;
		rightUpArmWorldTransform.rotate.z -= 0.09f;

		rightDownArmWorldTransform.translate.x += 0.013f;
		rightDownArmWorldTransform.translate.z += 0.03f;

		rightDownArmWorldTransform.rotate.y -= 0.03f;
	}



	//攻撃
	if (MotionCount_ == 1)
	{
		if (MotionTimer_ == 30)
		{
			MotionCount_ = 2;
		}

		UpBodyWorldTransform.rotate.y -= 0.04f / 2.0f;

		NeckWorldTransform.rotate.x -= 0.01f / 2.0f;
		NeckWorldTransform.rotate.y -= 0.01f / 2.0f;

		/*rightUpArmWorldTransform.translate.x -= 0.02f / 2.0f;*/
		rightUpArmWorldTransform.translate.y += 0.008f / 2.0f;
		rightUpArmWorldTransform.translate.z += 0.01f / 2.0f;

		rightUpArmWorldTransform.rotate.y -= 0.06f / 2.0f;

		rightDownArmWorldTransform.translate.x -= 0.013f / 2.0f;
		rightDownArmWorldTransform.translate.z -= 0.03f / 2.0f;
		rightDownArmWorldTransform.rotate.y += 0.13f / 2.0f;

	}

	//硬直
	if (MotionCount_ == 2)
	{
		isAttack_ = true;

		if (MotionTimer_ == 50)
		{
			MotionCount_ = 3;
			isAttack_ = false;
		}
	}

	//躰を戻す
	if (MotionCount_ == 3)
	{
		if (MotionTimer_ == 60)
		{
			MotionCount_ = 4;
		}
		UpBodyWorldTransform.rotate.y += 0.04f / 2.0f;

		NeckWorldTransform.rotate.x += 0.01f / 2.0f;
		NeckWorldTransform.rotate.y += 0.01f / 2.0f;

		/*rightUpArmWorldTransform.translate.x -= 0.02f / 2.0f;*/
		rightUpArmWorldTransform.translate.y -= 0.008f / 2.0f;
		rightUpArmWorldTransform.translate.z -= 0.01f / 2.0f;

		rightUpArmWorldTransform.rotate.y += 0.06f / 2.0f;

		rightDownArmWorldTransform.translate.x += 0.013f / 2.0f;
		rightDownArmWorldTransform.translate.z += 0.03f / 2.0f;
		rightDownArmWorldTransform.rotate.y -= 0.13f / 2.0f;
	}

	if (MotionCount_ == 4)
	{
		behaviorRequest_ = Behavior::kRoot;
	}
}



void Enemy::BehaviorRightHitUpdate()
{
	MotionTimer_++;
	
	//攻撃があたる
	if (MotionCount_ == 0)
	{
		if (MotionTimer_ == 5)
		{
			MotionCount_ = 1;
		}

		UpBodyWorldTransform.translate.z += 0.03f*2.0f;
		UpBodyWorldTransform.rotate.x += 0.01f*2.0f;
		UpBodyWorldTransform.rotate.y += 0.01f*2.0f;

		headWorldTransform.translate.x -= 0.01f*2.0f;
		headWorldTransform.rotate.x += 0.02f*2.0f;
		headWorldTransform.rotate.y += 0.05f*2.0f;

		leftUpArmWorldTransform.translate.x += 0.01f*2.0f;
		leftUpArmWorldTransform.translate.y -= 0.01f*2.0f;
		leftUpArmWorldTransform.translate.z -= 0.01f*2.0f;
		leftUpArmWorldTransform.rotate.y -= 0.09f*2.0f;

		rightUpArmWorldTransform.translate.y -= 0.01f*2.0f;
		rightUpArmWorldTransform.translate.z -= 0.01f*2.0f;
		rightUpArmWorldTransform.rotate.y += 0.05f*2.0f;
		rightUpArmWorldTransform.rotate.z -= 0.04f*2.0f;

		rightDownArmWorldTransform.translate.z += 0.02f*2.0f;
		rightDownArmWorldTransform.rotate.y += 0.05f * 2.0f;
	}

	//硬直
	if (MotionCount_ == 1)
	{
		if (MotionTimer_ == 15)
		{
			MotionCount_ = 3;
		}
	}

	//躰を戻す
	if (MotionCount_ == 2)
	{
		if (MotionTimer_ == 25)
		{
			MotionCount_ = 3;
		}

		UpBodyWorldTransform.translate.z -= 0.03f * 1.0f;
		UpBodyWorldTransform.rotate.x -= 0.01f * 1.0f;
		UpBodyWorldTransform.rotate.y -= 0.01f * 1.0f;

		headWorldTransform.translate.x += 0.01f * 1.0f;
		headWorldTransform.rotate.x -= 0.02f * 1.0f;
		headWorldTransform.rotate.y -= 0.05f * 1.0f;

		leftUpArmWorldTransform.translate.x -= 0.01f * 1.0f;
		leftUpArmWorldTransform.translate.y += 0.01f * 1.0f;
		leftUpArmWorldTransform.translate.z += 0.01f * 1.0f;
		leftUpArmWorldTransform.rotate.y += 0.09f * 1.0f;

		rightUpArmWorldTransform.translate.y += 0.01f * 1.0f;
		rightUpArmWorldTransform.translate.z += 0.01f * 1.0f;
		rightUpArmWorldTransform.rotate.y -= 0.05f * 1.0f;
		rightUpArmWorldTransform.rotate.z += 0.04f * 1.0f;

		rightDownArmWorldTransform.translate.z -= 0.02f * 1.0f;
		rightDownArmWorldTransform.rotate.y -= 0.05f * 1.0f;
	}

	if (MotionCount_ == 3)
	{
		behaviorRequest_ = Behavior::kRoot;
	}
}

void Enemy::BehaviorLeftHitUpdate()
{
	MotionTimer_++;

	//攻撃があたる
	if (MotionCount_ == 0)
	{
		if (MotionTimer_ == 5)
		{
			MotionCount_ = 1;
		}

		UpBodyWorldTransform.translate.z -= 0.03f * 2.0f;
		UpBodyWorldTransform.rotate.x += 0.01f * 2.0f;
		UpBodyWorldTransform.rotate.y -= 0.01f * 2.0f;

		headWorldTransform.translate.x += 0.01f * 2.0f;
		headWorldTransform.rotate.x += 0.02f * 2.0f;
		headWorldTransform.rotate.y -= 0.05f * 2.0f;

		leftUpArmWorldTransform.translate.x += 0.01f * 2.0f;
		leftUpArmWorldTransform.translate.y -= 0.01f * 2.0f;
		leftUpArmWorldTransform.translate.z -= 0.01f * 2.0f;
		leftUpArmWorldTransform.rotate.y -= 0.09f * 2.0f;

		rightUpArmWorldTransform.translate.y -= 0.01f * 2.0f;
		rightUpArmWorldTransform.translate.z -= 0.01f * 2.0f;
		rightUpArmWorldTransform.rotate.y += 0.05f * 2.0f;
		rightUpArmWorldTransform.rotate.z -= 0.04f * 2.0f;

		rightDownArmWorldTransform.translate.z += 0.02f * 2.0f;
		rightDownArmWorldTransform.rotate.y += 0.05f * 2.0f;
	}

	//硬直
	if (MotionCount_ == 1)
	{
		if (MotionTimer_ == 15)
		{
			MotionCount_ = 3;
		}
	}

	//躰を戻す
	if (MotionCount_ == 2)
	{
		if (MotionTimer_ == 25)
		{
			MotionCount_ = 3;
		}

		UpBodyWorldTransform.translate.z -= 0.03f * 1.0f;
		UpBodyWorldTransform.rotate.x += 0.01f * 1.0f;
		UpBodyWorldTransform.rotate.y += 0.01f * 1.0f;

		headWorldTransform.translate.x -= 0.01f * 1.0f;
		headWorldTransform.rotate.x -= 0.02f * 1.0f;
		headWorldTransform.rotate.y += 0.05f * 1.0f;

		leftUpArmWorldTransform.translate.x -= 0.01f * 1.0f;
		leftUpArmWorldTransform.translate.y += 0.01f * 1.0f;
		leftUpArmWorldTransform.translate.z += 0.01f * 1.0f;
		leftUpArmWorldTransform.rotate.y += 0.09f * 1.0f;

		rightUpArmWorldTransform.translate.y += 0.01f * 1.0f;
		rightUpArmWorldTransform.translate.z += 0.01f * 1.0f;
		rightUpArmWorldTransform.rotate.y -= 0.05f * 1.0f;
		rightUpArmWorldTransform.rotate.z += 0.04f * 1.0f;

		rightDownArmWorldTransform.translate.z -= 0.02f * 1.0f;
		rightDownArmWorldTransform.rotate.y -= 0.05f * 1.0f;
	}

	if (MotionCount_ == 3)
	{
		behaviorRequest_ = Behavior::kRoot;
	}
}

void Enemy::BehaviorRootInitialize()
{

	MotionTimer_ = 0;
	MotionCount_ = 0;

	std::random_device seedGenerator;
	std::mt19937 randomEngine(seedGenerator());
	std::uniform_real_distribution<float>distTime(120.0f, 180.0f);

	headModel_->SetTexHandle(headTex);

	AttackTimer_ = distTime(randomEngine);

	randomAttack = std::rand() % 2;

	UpBodyWorldTransform.translate = { 0.0f,-12.0f,40.0f };
	UpBodyWorldTransform.rotate = { 0.0f,-0.0f,0.0f };
	UpBodyWorldTransform.scale = { 10.0f,10.0f,10.0f };

	headWorldTransform.translate = { 0.0f,-0.05f,0.0f };
	headWorldTransform.rotate = { 0.0f,0.0f,0.0f };

	NeckWorldTransform.translate = { 0.0f,0.0f,0.0f };
	NeckWorldTransform.rotate = { 0.0f,0.0f,0.0f };

	leftUpArmWorldTransform.translate = { 0.2f,0.6f,0.1f };
	leftUpArmWorldTransform.rotate = { -0.0f,1.0f,-0.9f };

	rightUpArmWorldTransform.translate = { -0.2f,0.6f,0.0f };
	rightUpArmWorldTransform.rotate = { 0.0f,-1.0f,0.9f };

	leftDownArmWorldTransform.translate = { 0.4f,-0.0f,0.0f };
	leftDownArmWorldTransform.rotate = { 0.0f,1.0f,0.0f };

	rightDownArmWorldTransform.translate = { -0.4f,-0.01f,0.0f };
	rightDownArmWorldTransform.rotate = { 0.0f,-1.0f,-0.0f };

}

void Enemy::BehaviorLeftAttackInitialize()
{
	MotionTimer_ = 0;
	MotionCount_ = 0;

	UpBodyWorldTransform.translate = { 0.0f,-12.0f,40.0f };
	UpBodyWorldTransform.rotate = { 0.0f,-0.0f,0.0f };
	UpBodyWorldTransform.scale = { 10.0f,10.0f,10.0f };

	headWorldTransform.translate = { 0.0f,-0.05f,0.0f };
	headWorldTransform.rotate = { 0.0f,0.0f,0.0f };

	NeckWorldTransform.translate = { 0.0f,0.0f,0.0f };
	NeckWorldTransform.rotate = { 0.0f,0.0f,0.0f };

	leftUpArmWorldTransform.translate = { 0.2f,0.6f,0.1f };
	leftUpArmWorldTransform.rotate = { -0.0f,1.0f,-0.9f };

	rightUpArmWorldTransform.translate = { -0.2f,0.6f,0.0f };
	rightUpArmWorldTransform.rotate = { 0.0f,-1.0f,0.9f };

	leftDownArmWorldTransform.translate = { 0.4f,-0.0f,0.0f };
	leftDownArmWorldTransform.rotate = { 0.0f,1.0f,0.0f };

	rightDownArmWorldTransform.translate = { -0.4f,-0.01f,0.0f };
	rightDownArmWorldTransform.rotate = { 0.0f,-1.0f,-0.0f };
}

void Enemy::BehaviorRightAttackInitialize()
{
	MotionTimer_ = 0;
	MotionCount_ = 0;

	UpBodyWorldTransform.translate = { 0.0f,-12.0f,40.0f };
	UpBodyWorldTransform.rotate = { 0.0f,-0.0f,0.0f };
	UpBodyWorldTransform.scale = { 10.0f,10.0f,10.0f };

	headWorldTransform.translate = { 0.0f,-0.05f,0.0f };
	headWorldTransform.rotate = { 0.0f,0.0f,0.0f };

	NeckWorldTransform.translate = { 0.0f,0.0f,0.0f };
	NeckWorldTransform.rotate = { 0.0f,0.0f,0.0f };

	leftUpArmWorldTransform.translate = { 0.2f,0.6f,0.1f };
	leftUpArmWorldTransform.rotate = { -0.0f,1.0f,-0.9f };

	rightUpArmWorldTransform.translate = { -0.2f,0.6f,0.0f };
	rightUpArmWorldTransform.rotate = { 0.0f,-1.0f,0.9f };

	leftDownArmWorldTransform.translate = { 0.4f,-0.0f,0.0f };
	leftDownArmWorldTransform.rotate = { 0.0f,1.0f,0.0f };

	rightDownArmWorldTransform.translate = { -0.4f,-0.01f,0.0f };
	rightDownArmWorldTransform.rotate = { 0.0f,-1.0f,-0.0f };
}

void Enemy::BehaviorLeftHitInitialzie()
{
	MotionTimer_ = 0;
	MotionCount_ = 0;

	headModel_->SetTexHandle(headHitTex);

	UpBodyWorldTransform.translate = { 0.0f,-12.0f,40.0f };
	UpBodyWorldTransform.rotate = { 0.0f,-0.0f,0.0f };
	UpBodyWorldTransform.scale = { 10.0f,10.0f,10.0f };

	headWorldTransform.translate = { 0.0f,-0.05f,0.0f };
	headWorldTransform.rotate = { 0.0f,0.0f,0.0f };

	NeckWorldTransform.translate = { 0.0f,0.0f,0.0f };
	NeckWorldTransform.rotate = { 0.0f,0.0f,0.0f };

	leftUpArmWorldTransform.translate = { 0.2f,0.6f,0.1f };
	leftUpArmWorldTransform.rotate = { -0.0f,1.0f,-0.9f };

	rightUpArmWorldTransform.translate = { -0.2f,0.6f,0.0f };
	rightUpArmWorldTransform.rotate = { 0.0f,-1.0f,0.9f };

	leftDownArmWorldTransform.translate = { 0.4f,-0.0f,0.0f };
	leftDownArmWorldTransform.rotate = { 0.0f,1.0f,0.0f };

	rightDownArmWorldTransform.translate = { -0.4f,-0.01f,0.0f };
	rightDownArmWorldTransform.rotate = { 0.0f,-1.0f,-0.0f };
}

void Enemy::BehaviorRightHitInitialzie()
{
	MotionTimer_ = 0;
	MotionCount_ = 0;

	headModel_->SetTexHandle(headHitTex);

	UpBodyWorldTransform.translate = { 0.0f,-12.0f,40.0f };
	UpBodyWorldTransform.rotate = { 0.0f,-0.0f,0.0f };
	UpBodyWorldTransform.scale = { 10.0f,10.0f,10.0f };

	headWorldTransform.translate = { 0.0f,-0.05f,0.0f };
	headWorldTransform.rotate = { 0.0f,0.0f,0.0f };

	NeckWorldTransform.translate = { 0.0f,0.0f,0.0f };
	NeckWorldTransform.rotate = { 0.0f,0.0f,0.0f };

	leftUpArmWorldTransform.translate = { 0.2f,0.6f,0.1f };
	leftUpArmWorldTransform.rotate = { -0.0f,1.0f,-0.9f };

	rightUpArmWorldTransform.translate = { -0.2f,0.6f,0.0f };
	rightUpArmWorldTransform.rotate = { 0.0f,-1.0f,0.9f };

	leftDownArmWorldTransform.translate = { 0.4f,-0.0f,0.0f };
	leftDownArmWorldTransform.rotate = { 0.0f,1.0f,0.0f };

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
	UpBodyWorldTransform.translate.y = -12.0f+(std::sin(UpdownParameter_) * amplitude_);
}

void Enemy::SetEnemyHp(float hp)
{
	enemyHp -= hp;
	float result = (drawScale.x / enemyHp);
	drawScale.x -= result;

	hpSprite_->SetScale(drawScale);
}

