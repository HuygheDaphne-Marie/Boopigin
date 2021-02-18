#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Command.h"
//#include "Winerror.h"

boop::InputManager::InputManager()
{
	m_CurrentControllerStates.resize(m_MaxControllers);
}

bool boop::InputManager::ProcessInput()
{
	// Copy is ugly and ideally we swap between which we use instead of copying over every frame, not important for this small exercise though
	m_PreviousControllerStates = m_CurrentControllerStates;

	for (int controllerIndex = 0; controllerIndex < m_MaxControllers; controllerIndex++)
	{
		const DWORD isSuccessful = XInputGetState(controllerIndex, &m_CurrentControllerStates[controllerIndex]);
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}

	return true;
}
void boop::InputManager::HandleInput() const
{
	// we'll only care about one game pad for now, with multiple it'd be better to handle that in a separate object
	// since gamepads might have inputs mapped differently so they'd each need a map with commands
	// too much hassle for just this exercise right now
	for (const auto& pair : m_Commands)
	{
		if (GetButtonState(pair.first) == pair.second.KeyStateNeeded)
		{
			pair.second.pCommand->Execute();
		}
	}
}


bool boop::InputManager::IsPressed(ControllerButton button) const
{
	return Pressed(button, m_CurrentControllerStates);
}

boop::KeyState boop::InputManager::GetButtonState(ControllerButton button) const
{
	if (WasPressed(button))
	{
		if (IsPressed(button))
		{
			return KeyState::Held;
		}

		return KeyState::Released;
	}

	if (IsPressed(button))
	{
		return KeyState::Pressed;
	}

	return KeyState::Idle;
}

bool boop::InputManager::AddCommandToButton(ControllerButton button, Command* pCommand, KeyState neededKeyState)
{
	CommandInfo info = { neededKeyState, pCommand };
	return m_Commands.insert({ button, info }).second;
}

bool boop::InputManager::WasPressed(ControllerButton button) const
{
	return Pressed(button, m_PreviousControllerStates);
}

bool boop::InputManager::Pressed(ControllerButton button, const std::vector<XINPUT_STATE>& stateToUse) const
{
	for (const XINPUT_STATE& controllerState : stateToUse)
	{
		if (button == ControllerButton::LeftTrigger)
		{
			return controllerState.Gamepad.bLeftTrigger > 0;
		}
		if (button == ControllerButton::RightTrigger)
		{
			return controllerState.Gamepad.bRightTrigger > 0;
		}

		if (controllerState.Gamepad.wButtons & static_cast<std::underlying_type<ControllerButton>::type>(button))
			return true;

		// only ever checks first gamepad, this should be a part of game pad
		// Rest is just never reached
		// return controllerState.Gamepad.wButtons & static_cast<std::underlying_type<ControllerButton>::type>(button);
	}

	return false;
}
