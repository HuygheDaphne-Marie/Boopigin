#pragma once
#include <XInput.h>

enum class ControllerButton
{
	ButtonA = XINPUT_GAMEPAD_A,
	ButtonB = XINPUT_GAMEPAD_B,
	ButtonX = XINPUT_GAMEPAD_X,
	ButtonY = XINPUT_GAMEPAD_Y,
	DpadUp = XINPUT_GAMEPAD_DPAD_UP,
	DpadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
	DpadDown = XINPUT_GAMEPAD_DPAD_DOWN,
	DpadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
	Start = XINPUT_GAMEPAD_START,
	Back = XINPUT_GAMEPAD_BACK,
	LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
	RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	LeftThumbStick = XINPUT_GAMEPAD_LEFT_THUMB,
	RightThumbStick = XINPUT_GAMEPAD_RIGHT_THUMB,
	RightTrigger,
	LeftTrigger,
};

enum class KeyState
{
	Pressed,
	Held,
	Released,
	Idle
};
enum class KeyType
{
	Keyboard,
	XInputController
};
struct KeyInfo
{
	KeyType type;
	union
	{
		ControllerButton controllerButton;
		// Add SDL keycode here..
		// More types can be added too
	};
};