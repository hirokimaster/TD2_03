#pragma once
#include "Model.h"
#include "Sprite.h"
#include "Input.h"

class Animation {
public:
	/// <summary>
	/// 初期化
	/// </summary>
    void InitKO();

	void InitfadeOut();

	void InitFadeIn();

	/// <summary>
	/// 敵を倒したときの演出
	/// </summary>
	void AnimationKO();

	/// <summary>
	/// フェードアウト
	/// </summary>
	void FadeOut(bool startFlag);

	/// <summary>
	/// フェードイン
	/// </summary>
	void FadeIn(bool startFlag);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera"></param>
	void Draw(const Camera& camera);

private:
	/*-------------------------------
		  描画のフラグ
	----------------------------------*/
	bool DrawFadeIn_ = false;
	bool DrawFadeOut_ = false;
	bool DrawKO_ = false;
	/*-------------------------------
		  クリア演出用のやつ
	----------------------------------*/
	std::unique_ptr<Sprite>	spriteK_ = nullptr;
	std::unique_ptr<Sprite> spriteO_ = nullptr;
	//std::unique_ptr<Model> modelK_;
	//std::unique_ptr<Model> modelO_;
	uint32_t texHandleSpriteK_ = 0;
	uint32_t texHandleSpriteO_ = 0;
	Vector2 scaleK_{};
	Vector2 scaleO_{};
	bool isMoveK_ = false;
	bool isMoveO_ = false;
	float frameK_ = 0.0f;
	float endFrameK_ = 120.0f;
	float frameO_ = 0.0f;
	float endFrameO_ = 90.0f;
	/*--------------------------------
			シーン遷移
	----------------------------------*/
	std::unique_ptr<Sprite> spriteBlackIn_ = nullptr;
	std::unique_ptr<Sprite> spriteBlackOut_ = nullptr;
	uint32_t texHandleBlack_ = 0;
	uint32_t sceneTimer_ = 0;
	bool timerFlag_ = false;
	Vector4 color_ = {};
};
