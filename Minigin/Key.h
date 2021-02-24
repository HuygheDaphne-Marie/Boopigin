#pragma once
#include "MiniginPCH.h"
#include <XInput.h>

namespace boop
{
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
	// Add more enums if needed

	enum class KeyState
	{
		Pressed,
		Held,
		Released,
		Idle,
		BAD_INPUT
	};
	enum class KeyType
	{
		Keyboard,
		XInputController
	};
	struct KeyInfo
	{
		explicit KeyInfo(ControllerButton button)
		{
			type = KeyType::XInputController;
			controllerButton = button;
		}
		
		KeyType type;
		union
		{
			ControllerButton controllerButton;
			// Add SDL keycode here..
			// More types can be added too
		};

		bool operator==(const KeyInfo& other) const
		{
			return type == other.type && controllerButton == other.controllerButton;
		}
	};
	struct KeyInfoHasher
	{
		size_t operator()(const KeyInfo& keyInfo) const
		{
			return reinterpret_cast<size_t>(&keyInfo);
		}
	};
}