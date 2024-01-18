#pragma once

class Enemy {
public:
	~Enemy();
	void Initialize(int hp);
	void Update();
	void Draw();

	void SetEnemyHp(int hp) { enemyHp -= hp;}

	int GetEnemyHp() { return enemyHp; }

private:
	int enemyHp;
};