#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <XInput.h>
#pragma comment(lib, "XInput.lib")

#include <vector>
#include <unordered_map>



namespace boop
{
	class Command;
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
	struct CommandInfo
	{
		KeyState KeyStateNeeded;
		Command* pCommand;
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

	class InputManager final : public Singleton<InputManager> 
	{
	public:
		bool ProcessInput();
		void HandleInput() const;

		[[nodiscard]] bool IsPressed(ControllerButton button) const;
		[[nodiscard]] KeyState GetButtonState(ControllerButton button) const;

		bool AddCommandToButton(ControllerButton button, Command* pCommand, KeyState neededKeyState);

	private:
		friend class Singleton<InputManager>;
		InputManager();

		[[nodiscard]] bool WasPressed(ControllerButton button) const;
		[[nodiscard]] bool Pressed(ControllerButton button, const std::vector<XINPUT_STATE>& stateToUse) const;

		// Feels like it'd be better to have a gamepad object which holds a state
		// and then also handles input and has an IsPressed,
		// that way inputhandler would just be keeping these objects and looping over them
		// or calling only the is pressed for a specific gamepad belonging to a certain player
		std::vector<XINPUT_STATE> m_PreviousControllerStates;
		std::vector<XINPUT_STATE> m_CurrentControllerStates;
		const int m_MaxControllers = 4;

		std::unordered_map<ControllerButton, CommandInfo> m_Commands;
	};

}

