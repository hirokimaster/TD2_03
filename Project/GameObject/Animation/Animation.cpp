#include "Animation.h"

Animation* Animation::GetInstance()
{
	static Animation instance;
	return &instance;
}

void Animation::Initialize()
{
	// spriteとtextureとmodel初期化
	Animation::GetInstance()->modelK_.reset(Model::CreateObj("Production/k.obj"));
	Animation::GetInstance()->modelO_.reset(Model::CreateObj("Production/o.obj"));
	Animation::GetInstance()->texHandleSpriteK_ = TextureManager::Load("resources/Production/yellow.png");
	Animation::GetInstance()->texHandleSpriteO_ = TextureManager::Load("resources/Production/yellow.png");
	Animation::GetInstance()->modelK_->SetTexHandle(Animation::GetInstance()->texHandleSpriteK_);
	Animation::GetInstance()->modelO_->SetTexHandle(Animation::GetInstance()->texHandleSpriteO_);
	Animation::GetInstance()->texHandleBlack_ = TextureManager::Load("resources/black.png");
	Animation::GetInstance()->spriteBlack_.reset(Sprite::Create({ 0,0 }, { 1280.0f,720.0f }, { 1.0f,1.0f,1.0f,0.0f }));
}

void Animation::InitKO()
{
	Animation::GetInstance()->DrawK_ = false;
	Animation::GetInstance()->DrawO_ = false;
	Animation::GetInstance()->frameK_ = 0;
	Animation::GetInstance()->frameO_ = 0;
	Animation::GetInstance()->transformK_.Initialize();
	Animation::GetInstance()->transformO_.Initialize();
	Animation::GetInstance()->transformK_.translate = { -7.0f, 3.0f, 50.0f };
	Animation::GetInstance()->transformO_.translate = { 7.0f,3.0f,50.0f };
}

void Animation::InitfadeOut()
{
	Animation::GetInstance()->sceneTimer_ = 0;
	Animation::GetInstance()->color2_ = { 1.0f,1.0f,1.0f,1.0f };
	Animation::GetInstance()->DrawFadeOut_ = true;
}

void Animation::InitFadeIn()
{
	Animation::GetInstance()->sceneTimer_ = 0;
	Animation::GetInstance()->color_ = { 1.0f,1.0f,1.0f,0.0f };
	Animation::GetInstance()->DrawFadeIn_ = true;
}

void Animation::ModelDestruction()
{
	Animation::GetInstance()->modelK_.reset();
	Animation::GetInstance()->modelO_.reset();
}

void Animation::SpriteDestruction()
{
	Animation::GetInstance()->spriteBlack_.reset();
}

Vector3 Animation::Move(const Vector3& startPos, const Vector3& endPos, float duration, float currentTime)
{
	// 時間がdurationを超えたら終了位置に移動する
	if (currentTime >= duration) {
		return endPos;
	}

	float t = currentTime / duration;
	float easedT = easeInSine(t);
	Vector3 distance = { endPos.x - startPos.x, endPos.y - startPos.y, endPos.z - startPos.z };
	return { startPos.x + (easedT * distance.x), startPos.y + (easedT * distance.y), startPos.z + (easedT * distance.z) };

}

Vector3 Animation::Rotate(Vector3& currentRotation, const Vector3& initialRotation, const Vector3& targetRotation, float duration, float currentTime)
{
	// 時間がdurationを超えたら終了位置に移動する
	if (currentTime >= duration) {
		return targetRotation;
	}

	float t = currentTime / duration;
	float easedT = easeInSine(t);

	return{
	currentRotation.x = initialRotation.x + easedT * (targetRotation.x - initialRotation.x),
	currentRotation.y = initialRotation.y + easedT * (targetRotation.y - initialRotation.y),
	currentRotation.z = initialRotation.z + easedT * (targetRotation.z - initialRotation.z),
	};
}

void Animation::Shake(Camera& camera)
{
	if (Animation::GetInstance()->isShakeK_) {

		std::random_device seedGenerator;
		std::mt19937 randomEngine(seedGenerator());
		std::uniform_real_distribution<float>distribution(-0.05f, 0.05f);

		camera.translate.x = camera.translate.x + distribution(randomEngine);
		camera.translate.y = camera.translate.y + distribution(randomEngine);
	}
	else if (Animation::GetInstance()->isShakeO_) {
		std::random_device seedGenerator2;
		std::mt19937 randomEngine2(seedGenerator2());
		std::uniform_real_distribution<float>distribution2(-0.05f, 0.05f);

		camera.translate.x = camera.translate.x + distribution2(randomEngine2);
		camera.translate.y = camera.translate.y + distribution2(randomEngine2);
	}

	if (!Animation::GetInstance()->isShakeK_ && !Animation::GetInstance()->isShakeO_) {
		camera.translate = { 0.0f,1.0f,-10.0f };
		camera.rotate.x = 0.15f;
	}
}

void Animation::AnimationKO(Camera& camera)
{


	Animation::GetInstance()->isMoveK_ = true;
	Animation::GetInstance()->isMoveO_ = true;
	Animation::GetInstance()->DrawK_ = true;


	if (Animation::GetInstance()->isMoveK_) {
		++Animation::GetInstance()->frameK_;
	}

	if (Animation::GetInstance()->frameK_ > Animation::GetInstance()->endFrameK_ && Animation::GetInstance()->frameK_ <= 135.0f) {
		Animation::GetInstance()->isShakeK_ = true;
	}

	if (Animation::GetInstance()->isMoveO_ && Animation::GetInstance()->frameK_ >= 70.0f) {
		++Animation::GetInstance()->frameO_;
		Animation::GetInstance()->DrawO_ = true;
	}

	if (Animation::GetInstance()->frameO_ >= 90.0f && Animation::GetInstance()->frameO_ <= 105.0f) {
		Animation::GetInstance()->isShakeO_ = true;
	}

	// 画面を揺らす
	if (Animation::GetInstance()->frameK_ >= 135.0f) {
		Animation::GetInstance()->isShakeK_ = false;
	}

	if (Animation::GetInstance()->frameO_ >= 105.0f) {
		Animation::GetInstance()->isShakeO_ = false;
	}

	Shake(camera);

	Animation::GetInstance()->transformK_.translate = Move({ -20.0f, 3.0f, 50.0f }, { -1.0f, 0.0f,-5.0f }, Animation::GetInstance()->endFrameK_, Animation::GetInstance()->frameK_);
	Animation::GetInstance()->transformO_.translate = Move({ 20.0f, 3.0f, 50.0f }, { 0.3f, 0.0f,-5.0f }, Animation::GetInstance()->endFrameO_, Animation::GetInstance()->frameO_);

	Animation::GetInstance()->transformK_.rotate = Rotate(Animation::GetInstance()->transformK_.rotate, { 0.0f,0.0f,0.0f }, { 0.0f, (float)std::numbers::pi * 3.9f, 0.0f }, Animation::GetInstance()->endFrameK_, Animation::GetInstance()->frameK_);
	Animation::GetInstance()->transformO_.rotate = Rotate(Animation::GetInstance()->transformO_.rotate, { 0.0f,0.0f,0.0f }, { 0.0f, (float)std::numbers::pi * 4.1f, 0.0f }, Animation::GetInstance()->endFrameO_, Animation::GetInstance()->frameO_);

	Animation::GetInstance()->transformK_.UpdateMatrix();
	Animation::GetInstance()->transformO_.UpdateMatrix();

}

void Animation::FadeOut(bool startFlag)
{
	if (startFlag) {
		Animation::GetInstance()->sceneTimer_++;

		if (Animation::GetInstance()->sceneTimer_ >= 10) {
			Animation::GetInstance()->color2_.w -= 0.01f;
			Animation::GetInstance()->spriteBlack_->SetColor({ Animation::GetInstance()->color2_ });
		}
	}

	if (Animation::GetInstance()->color2_.w <= 0.0f) {
		startFlag = false;
	}
}

void Animation::FadeIn(bool startFlag)
{
	if (startFlag) {
		Animation::GetInstance()->sceneTimer_++;

		if (Animation::GetInstance()->sceneTimer_ >= 10) {
			Animation::GetInstance()->color_.w += 0.01f;
			Animation::GetInstance()->spriteBlack_->SetColor({ Animation::GetInstance()->color_ });
		}
	}

	if (Animation::GetInstance()->color_.w >= 1.0f) {
		startFlag = false;
	}
}

void Animation::Draw(const Camera& camera)
{

	if (Animation::GetInstance()->DrawK_) {
		Animation::GetInstance()->modelK_->Draw(Animation::GetInstance()->transformK_, camera);
	}

	if (Animation::GetInstance()->DrawO_) {
		Animation::GetInstance()->modelO_->Draw(Animation::GetInstance()->transformO_, camera);
	}

	if (Animation::GetInstance()->DrawFadeIn_) {
		Animation::GetInstance()->spriteBlack_->Draw(camera, Animation::GetInstance()->texHandleBlack_);
	}

	if (Animation::GetInstance()->DrawFadeOut_) {
		Animation::GetInstance()->spriteBlack_->Draw(camera, Animation::GetInstance()->texHandleBlack_);
	}

}
