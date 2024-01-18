#include "Enemy.h"
#include "imgui.h"

Enemy::~Enemy()
{
}

void Enemy::Initialize(int hp)
{
	enemyHp = hp;
}

void Enemy::Update()
{
	ImGui::Begin("Enemy HP");
	ImGui::Text("%d", enemyHp);
	ImGui::End();
}

void Enemy::Draw()
{

}
