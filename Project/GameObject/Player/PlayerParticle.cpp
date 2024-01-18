#include "PlayerParticle.h"

void PlayerParticle::Initialize()
{
	texHandle_ = TextureManager::Load("resources/uvChecker.png");
	particle_ = std::make_unique<ParticleSystem>();
	randomEngine_ = particle_->random();
	particle_->Initialize("plane.obj");
	particle_->SetTexHandle(texHandle_);
	
	particleProperty_.distribution = { -1.0f,1.0f };
	particleProperty_.distVelocity = { -1.0f,1.0f };
	particleProperty_.distColor = { 0.0f,1.0f };
	particleProperty_.distTime = { 1.0f,3.0f };
	particle_->SetParticleProperty(particleProperty_);
	for (std::list<Particle>::iterator particleItr = particles_.begin();
		particleItr != particles_.end(); ++particleItr) {
		(*particleItr).worldTransform.translate.z = 200.0f;
		(*particleItr).worldTransform.scale = { 0.1f,0.1f,0.1f };
	}

	emit_.count = 10;
	emit_.frequency = 0.5f;
	emit_.frequencyTime = 0.0f;

}

void PlayerParticle::Update()
{

	emit_.frequencyTime += deltaTime_;
	if (emit_.frequency <= emit_.frequencyTime) {
		particles_.splice(particles_.end(), particle_->Emission(emit_, randomEngine_));
		emit_.frequencyTime -= emit_.frequency;
	}


	for (std::list<Particle>::iterator particleItr = particles_.begin();
		particleItr != particles_.end(); ++particleItr) {

		

		(*particleItr).worldTransform.translate = Add((*particleItr).worldTransform.translate, Multiply(deltaTime_, (*particleItr).velocity));
		(*particleItr).worldTransform.UpdateMatrix();

	}

}

void PlayerParticle::Draw(const Camera& camera)
{
	particle_->Draw(particles_, camera);
}
