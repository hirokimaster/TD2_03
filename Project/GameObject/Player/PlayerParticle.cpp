#include "PlayerParticle.h"
#include "Player/Player.h"

void PlayerParticle::RightInitialize(const Vector3& position)
{
	texHandle_ = TextureManager::Load("resources/uvChecker.png");
	particle_ = std::make_unique<ParticleSystem>();
	randomEngine_ = particle_->random();
	particle_->SetSrvIndex(100);
	particle_->Initialize("cube.obj");
	particle_->SetTexHandle(texHandle_);
	particleProperty_.distribution = { -0.5f,0.5f };
	particleProperty_.distVelocity = { -10.0f,10.0f };
	particleProperty_.distColor = { 1.0f,1.0f };
	particleProperty_.distTime = { 1.0f,3.0f };
	particle_->SetParticleProperty(particleProperty_);
	emit_.count = 50;

	particles_.splice(particles_.end(), particle_->Emission(emit_, randomEngine_));

	for (std::list<Particle>::iterator particleItr = particles_.begin();
		particleItr != particles_.end(); ++particleItr) {
		(*particleItr).worldTransform.scale = { 0.05f,0.05f,0.05f };
		(*particleItr).worldTransform.translate = position;
	}

}

void PlayerParticle::LeftInitialize(const Vector3& position)
{
	texHandle_ = TextureManager::Load("resources/uvChecker.png");
	particle_ = std::make_unique<ParticleSystem>();
	randomEngine_ = particle_->random();
	particle_->SetSrvIndex(120);
	particle_->Initialize("cube.obj");
	particle_->SetTexHandle(texHandle_);
	particleProperty_.distribution = { -0.5f,0.5f };
	particleProperty_.distVelocity = { -10.0f,10.0f };
	particleProperty_.distColor = { 1.0f,1.0f };
	particleProperty_.distTime = { 1.0f,3.0f };
	particle_->SetParticleProperty(particleProperty_);
	emit_.count = 50;

	particles_.splice(particles_.end(), particle_->Emission(emit_, randomEngine_));

	for (std::list<Particle>::iterator particleItr = particles_.begin();
		particleItr != particles_.end(); ++particleItr) {
		(*particleItr).worldTransform.scale = { 0.05f,0.05f,0.05f };
		(*particleItr).worldTransform.translate = position;
	}
}

void PlayerParticle::Update()
{
	// 動き
	for (std::list<Particle>::iterator particleItr = particles_.begin();
		particleItr != particles_.end(); ++particleItr) {
		(*particleItr).worldTransform.translate = Add((*particleItr).worldTransform.translate, Multiply(deltaTime_, (*particleItr).velocity));
		(*particleItr).worldTransform.UpdateMatrix();

	}

	// 時間で消滅
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

#ifdef _DEBUG
	ImGui::Begin("particleFlag");
	ImGui::Text("flag %d", emitParticles_);
	ImGui::End();
#endif // _DEBUG

}

void PlayerParticle::Draw(const Camera& camera)
{
	particle_->Draw(particles_, camera);
}
