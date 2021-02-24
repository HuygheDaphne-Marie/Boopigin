#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <XInput.h>
#pragma comment(lib, "XInput.lib")

#include <vector>
#include <unordered_map>

#include "Key.h"

namespace boop
{
	class Command;
	struct CommandInfo
	{
		KeyState KeyStateNeeded;
		Command* pCommand;
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

