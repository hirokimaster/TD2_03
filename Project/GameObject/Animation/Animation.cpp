#include "Animation.h"

void Animation::InitKO()
{
	// クリア演出用のやつ
	modelK_.reset(Model::CreateObj("Production/k.obj"));
	modelO_.reset(Model::CreateObj("Production/o.obj"));
	texHandleSpriteK_ = TextureManager::Load("resources/uvChecker.png");
	texHandleSpriteO_ = TextureManager::Load("resources/uvChecker.png");
	modelK_->SetTexHandle(texHandleSpriteK_);
	modelO_->SetTexHandle(texHandleSpriteO_);
	frameK_ = 0;
	frameO_ = 0;
	DrawK_ = false;
	DrawO_ = false;
	transformK_.Initialize();
	transformO_.Initialize();
	transformK_.translate = { -7.0f, 3.0f, 50.0f };
	transformO_.translate = { 7.0f,3.0f,50.0f };
	
}

void Animation::InitfadeOut()
{
	// フェードアウト用
	texHandleBlack_ = TextureManager::Load("resources/black.png");
	spriteBlackOut_.reset(Sprite::Create({ 0,0 }, { 1280.0f,720.0f }, { 1.0f,1.0f,1.0f,1.0f }));
	color_ = { 1.0f,1.0f,1.0f,1.0f };
	DrawFadeOut_ = true;
}

void Animation::InitFadeIn()
{
	// フェードイン用
	texHandleBlack_ = TextureManager::Load("resources/black.png");
	spriteBlackIn_.reset(Sprite::Create({ 0,0 }, { 1280.0f,720.0f }, { 1.0f,1.0f,1.0f,0.0f }));
	color_ = { 1.0f,1.0f,1.0f,0.0f };
	DrawFadeIn_ = true;
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

	if (currentTime >= duration) {
		return targetRotation;
	}
	// 時間に対するイージング関数の適用
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
	if(isShakeK_){

		std::random_device seedGenerator;
		std::mt19937 randomEngine(seedGenerator());
		std::uniform_real_distribution<float>distribution(-0.05f, 0.05f);

		camera.translate.x = camera.translate.x + distribution(randomEngine);
		camera.translate.y = camera.translate.y + distribution(randomEngine);
	}
	else if (isShakeO_) {
		std::random_device seedGenerator2;
		std::mt19937 randomEngine2(seedGenerator2());
		std::uniform_real_distribution<float>distribution2(-0.05f, 0.05f);

		camera.translate.x = camera.translate.x + distribution2(randomEngine2);
		camera.translate.y = camera.translate.y + distribution2(randomEngine2);
	}

	if (!isShakeK_ && !isShakeO_) {
		camera.translate = { 0.0f,1.0f,-10.0f };
		camera.rotate.x = 0.15f;
	}
}

void Animation::AnimationKO(Camera& camera)
{
	if (Input::GetInstance()->PressedKey(DIK_P)) {
		isMoveK_ = true;
		isMoveO_ = true;
		DrawK_ = true;
	}

	if (isMoveK_) {
		++frameK_;
	}

	if (frameK_ > endFrameK_ && frameK_ <= 135.0f) {
		isShakeK_ = true;
	}

	if (isMoveO_ && frameK_ >= 70.0f) {
		++frameO_;
		DrawO_ = true;
	}

	if (frameO_ >= 90.0f && frameO_ <= 105.0f) {
		isShakeO_ = true;
	}

	// 画面を揺らす
	if (frameK_ >= 135.0f) {
		isShakeK_ = false;
	}

	if (frameO_ >= 105.0f) {
		isShakeO_ = false;
	}

	Shake(camera);
	
	transformK_.translate = Move({ -20.0f, 3.0f, 50.0f }, { -1.0f, 0.0f,-5.0f }, endFrameK_, frameK_);
	transformO_.translate = Move({ 20.0f, 3.0f, 50.0f }, { 0.3f, 0.0f,-5.0f }, endFrameO_, frameO_);

	transformK_.rotate = Rotate(transformK_.rotate, { 0.0f,0.0f,0.0f }, { 0.0f, (float)std::numbers::pi * 3.9f, 0.0f }, endFrameK_, frameK_);
	transformO_.rotate = Rotate(transformO_.rotate, { 0.0f,0.0f,0.0f }, { 0.0f, (float)std::numbers::pi * 4.1f, 0.0f }, endFrameO_, frameO_);

	transformK_.UpdateMatrix();
	transformO_.UpdateMatrix();

}

void Animation::FadeOut(bool startFlag)
{
	if (startFlag) {
		sceneTimer_++;

		if (sceneTimer_ >= 10) {
			//color_.w -= 0.001f;
			spriteBlackOut_->SetColor({ color_ });
		}
	}
}

void Animation::FadeIn(bool startFlag)
{
	if (startFlag) {
		sceneTimer_++;

		if (sceneTimer_ >= 10) {
			color_.w += 0.008f;
			spriteBlackIn_->SetColor({ color_ });
		}
	}
}

void Animation::Draw(const Camera& camera)
{

	if (DrawK_) {
		modelK_->Draw(transformK_, camera);
	}

	if (DrawO_) {
		modelO_->Draw(transformO_, camera);
	}

	if (DrawFadeIn_) {
		spriteBlackIn_->Draw(camera, texHandleBlack_);
	}

	if (DrawFadeOut_) {
		spriteBlackOut_->Draw(camera, texHandleBlack_);
	}

}
