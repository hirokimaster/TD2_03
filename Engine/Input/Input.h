#pragma once
#include"WinApp.h"
#include <cassert>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <Xinput.h>
#pragma comment(lib,"xinput.lib")
#pragma comment(lib,"dinput8.lib")

class Input{
public:
	struct ButtonState {
		bool isPressed;
		bool wasPressed;

		ButtonState() : isPressed(false), wasPressed(false) {}
	};

	static Input* GetInstance();

	static void Initialize();

	static void Update();

	bool PushKey(uint8_t keyNum);

	bool PressedKey(uint32_t keyNum);

	static bool GetJoystickState();

	bool GetJoystickState(XINPUT_STATE &out);

	bool PressedButton(WORD button);

	/// <summary>
	/// padの振動
	/// </summary>
	/// <param name="vibration"></param>
	/// <param name="rightMoterSpeed"></param>
	/// <param name="leftMoterSpeed"></param>
	/// <param name="vibrationTime"></param>
	void GamePadVibration(XINPUT_VIBRATION vibration, uint32_t rightMoterSpeed, uint32_t leftMoterSpeed, float vibrationTime);

	//void SetJoystickDeadZone(int32_t deadZoneL, int32_t deadZoneR);

	void UpdateButtonState(ButtonState& state, bool isPressed);


private:

	IDirectInput8* directInput = nullptr;
	IDirectInputDevice8* keyboard = nullptr;

	BYTE keys[256] = {};
	BYTE preKeys[256] = {};

	bool isInitialize = false;

	XINPUT_STATE state_{};
	XINPUT_STATE preState_{};

	//0x80=押している状態
	//0x00=押してない状態
	Input() = default;
	~Input() = default;
	Input(const Input&) = delete;
	const Input& operator=(const Input&) = delete;
};