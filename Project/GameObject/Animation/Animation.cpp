#include "Animation.h"

void Animation::InitKO()
{
	// クリア演出用のやつ
	modelK_.reset(Model::CreateObj("Production/k.obj"));
	modelO_.reset(Model::CreateObj("Production/o.obj"));
	texHandleSpriteK_ = TextureManager::Load("resources/black.png");
	texHandleSpriteO_ = TextureManager::Load("resources/black.png");
	modelK_->SetTexHandle(texHandleSpriteK_);
	modelO_->SetTexHandle(texHandleSpriteO_);
	DrawKO_ = true;
	transformK_.Initialize();
	transformO_.Initialize();
	transformK_.translate = { -7.0f, 3.0f, 150.0f };
	transformO_.translate = { 7.0f,3.0f,150.0f };
	
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

	transformK_.translate.z = 150.0f + (5.0f - 150.0f) * easeInSine(frameK_ / endFrameK_);
	transformO_.translate.z = 150.0f + (5.0f - 150.0f) * easeInSine(frameK_ / endFrameK_);

	//transformK_.translate.x = -7.0f + (-4.0f - 7.0f) * easeInSine(frameO_ / endFrameO_);
	//transformO_.translate.x = 7.0f + (4.0f - 7.0f) * easeInSine(frameO_ / endFrameO_);

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
	
	if (isMoveK_ && DrawKO_) {
		modelK_->Draw(transformK_, camera);
	}

	if (isMoveO_ && DrawKO_) {
		modelO_->Draw(transformO_, camera);
	}

	if (DrawFadeIn_) {
		spriteBlackIn_->Draw(camera, texHandleBlack_);
	}

	if (DrawFadeOut_) {
		spriteBlackOut_->Draw(camera, texHandleBlack_);
	}
	
}
