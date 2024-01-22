#pragma once
#include "ParticleSystem/ParticleSystem.h"
#include "Player/Player.h"

class PlayerParticle {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const Camera& camera);

	// setter
	void SetPlayer(Player* player) { player_ = player; }

private:

	std::unique_ptr<ParticleSystem> particle_ = {};
	std::list<Particle> particles_ = {};
	const float  deltaTime_ = 1.0f / 60.0f;
	Emitter emit_{};
	std::mt19937 randomEngine_;
	uint32_t texHandle_ = 0;
	Particle part_{};
	ParticleProperty particleProperty_{};
	Player* player_ = nullptr;
};
