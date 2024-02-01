#include "Animation.h"

void Animation::InitKO()
{
	// クリア演出用のやつ
	spriteK_.reset(Sprite::Create({ 0,0 }, { 500.0f,500.0f }));
	spriteO_.reset(Sprite::Create({ 780.0f,0 }, { 500.0f,500.0f }));
	texHandleSpriteK_ = TextureManager::Load("resources/k.png");
	texHandleSpriteO_ = TextureManager::Load("resources/o.png");
	scaleK_ = { 0.1f,0.1f };
	scaleO_ = { 0.1f,0.1f };
	DrawKO_ = true;
	
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

void Animation::AnimationKO()
{
	if (Input::GetInstance()->PressedKey(DIK_P)) {
		isMoveK_ = true;
		isMoveO_ = true;
	}

	if (isMoveK_) {
		++frameK_;
	}

	if (frameK_ >= endFrameK_) {
		isMoveK_ = false;
	}

	if (isMoveO_ && !isMoveK_) {
		++frameO_;
	}

	if (frameO_ >= endFrameO_) {
		isMoveO_ = false;
	}

	spriteK_->SetScale(scaleK_);
	scaleK_.x = 0.1f + (1.0f - 0.1f) * easeInSine(frameK_ / endFrameK_);
	scaleK_.y = 0.1f + (1.0f - 0.1f) * easeInSine(frameK_ / endFrameK_);

	spriteO_->SetScale(scaleO_);
	scaleO_.x = 0.1f + (1.0f - 0.1f) * easeInSine(frameO_ / endFrameO_);
	scaleO_.y = 0.1f + (1.0f - 0.1f) * easeInSine(frameO_ / endFrameO_);

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
	if (isMoveK_ && DrawKO_) {
		spriteK_->Draw(camera, texHandleSpriteK_);
	}
	
	if (isMoveO_ && DrawKO_) {
		spriteO_->Draw(camera, texHandleSpriteO_);
	}

	if (DrawFadeIn_) {
		spriteBlackIn_->Draw(camera, texHandleBlack_);
	}

	if (DrawFadeOut_) {
		spriteBlackOut_->Draw(camera, texHandleBlack_);
	}
	
}
