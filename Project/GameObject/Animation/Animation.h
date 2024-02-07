#pragma once
#include "Model.h"
#include "Sprite.h"
#include "Input.h"
#include <numbers>
#include <random>

class Animation {
public: // メンバ関数

	/// <summary>
	/// インスタンス
	/// </summary>
	/// <returns></returns>
	static Animation* GetInstance();

	void static Initialize();

	/// <summary>
	/// 初期化
	/// </summary>
    static void InitKO();

	static void InitfadeOut();

	static void InitFadeIn();

	/// <summary>
	/// 敵を倒したときの演出
	/// </summary>
	static void AnimationKO(Camera& camera);

	/// <summary>
	/// フェードアウト
	/// </summary>
	static void FadeOut(bool startFlag);

	/// <summary>
	/// フェードイン
	/// </summary>
	static void FadeIn(bool startFlag);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera"></param>
	static void Draw(const Camera& camera);

	/// <summary>
	/// 破棄
	/// </summary>
	static void ModelDestruction();

private: // クラス内でしか使わない関数

	static Vector3 Move(const Vector3& startPos, const Vector3& endPos, float duration, float currentTime);

	static Vector3 Rotate(Vector3& currentRotation, const Vector3& initialRotation, const Vector3& targetRotation,
		float duration, float currentTime);

	static void Shake(Camera& camera);

private:

	//Animation() = default;
	//~Animation() = default;
	//Animation(const Animation&) = delete;
	//const Animation& operator=(const Animation&) = delete;

private: // メンバ変数

	/*-------------------------------
		  描画のフラグ
	----------------------------------*/
	bool DrawFadeIn_ = false;
	bool DrawFadeOut_ = false;
	bool DrawK_ = false;
	bool DrawO_ = false;
	/*-------------------------------
		  クリア演出用のやつ
	----------------------------------*/
	WorldTransform transformK_{};
	WorldTransform transformO_{};
	std::unique_ptr<Model> modelK_;
	std::unique_ptr<Model> modelO_;
	uint32_t texHandleSpriteK_ = 0;
	uint32_t texHandleSpriteO_ = 0;
	Vector2 scaleK_{};
	Vector2 scaleO_{};
	bool isMoveK_;
	bool isMoveO_;
	float frameK_ = 0.0f;
	float endFrameK_ = 120.0f;
	float frameO_ = 0.0f;
	float endFrameO_ = 90.0f;
	float shakeTime_ = 0;
	bool isShakeK_ = false;
	bool isShakeO_ = false;
	/*--------------------------------
			シーン遷移
	----------------------------------*/
	std::unique_ptr<Sprite> spriteBlack_ = nullptr;
	uint32_t texHandleBlack_ = 0;
	uint32_t sceneTimer_ = 0;
	bool timerFlag_ = false;
	Vector4 color_ = {};
};
