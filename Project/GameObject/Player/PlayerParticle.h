#pragma once
#include "ParticleSystem/ParticleSystem.h"
class Player;

class PlayerParticle {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void RightInitialize(const Vector3& position);

	void LeftInitialize(const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const Camera& camera);

	// setter
	void SetPosition(const Vector3& position) { position_ = position; }

	bool IsDead() const { return isDead_; }

private:

	std::unique_ptr<ParticleSystem> particle_ = {};
	std::list<Particle> particles_ = {};
	const float  deltaTime_ = 1.0f / 60.0f;
	Emitter emit_{};
	std::mt19937 randomEngine_;
	uint32_t texHandle_ = 0;
	ParticleProperty particleProperty_{};
	Vector3 position_ = {};
	bool emitParticles_;
	bool isDead_;
	static const int32_t kLifeTime_ = 60 * 5;
	int32_t deathTimer_ = kLifeTime_;
};
