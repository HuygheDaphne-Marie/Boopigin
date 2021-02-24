#include "MiniginPCH.h"
#include "ControllerManager.h"

#include <Windows.h>
#include <XInput.h>
#pragma comment(lib, "XInput.lib")

//#include "Winerror.h"

boop::ControllerManager::ControllerManager(int controllerId)
	: m_ControllerId(controllerId)
	, m_IsControllerStateOneCurrent(false)
	, m_ControllerStateOne{}
	, m_ControllerStateTwo{}
{
}

bool boop::ControllerManager::ProcessInput()
{
	m_IsControllerStateOneCurrent = !m_IsControllerStateOneCurrent;
	
	const DWORD isSuccessful = XInputGetState(m_ControllerId, &GetCurrentState());

	return true;
	//Todo: Should return whether the game loop should continue, for now we'll just let it continue forever,
	//todo:  this might also just always be handled by the inputManager
}
boop::KeyState boop::ControllerManager::GetKeyState(const KeyInfo& keyInfo) const
{
	if (keyInfo.type != KeyType::XInputController)
	{
		return KeyState::BAD_INPUT;
	}

	const ControllerButton& button = keyInfo.controllerButton;
	
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

bool boop::ControllerManager::IsPressed(ControllerButton button) const
{
	return Pressed(button, GetCurrentState());
}
bool boop::ControllerManager::WasPressed(ControllerButton button) const
{
	return Pressed(button, GetPreviousState());
}
bool boop::ControllerManager::Pressed(ControllerButton button, const XINPUT_STATE& stateToUse) const
{
	if (button == ControllerButton::LeftTrigger)
	{
		return stateToUse.Gamepad.bLeftTrigger > 0;
	}
	if (button == ControllerButton::RightTrigger)
	{
		return stateToUse.Gamepad.bRightTrigger > 0;
	}

	if (stateToUse.Gamepad.wButtons & static_cast<std::underlying_type<ControllerButton>::type>(button))
		return true;

	return false;
}

// Helpers
XINPUT_STATE& boop::ControllerManager::GetCurrentState()
{
	if (m_IsControllerStateOneCurrent)
	{
		return m_ControllerStateOne;
	}
	return m_ControllerStateTwo;
}
XINPUT_STATE& boop::ControllerManager::GetPreviousState()
{
	if (m_IsControllerStateOneCurrent)
	{
		return m_ControllerStateTwo;
	}
	return m_ControllerStateOne;
}
const XINPUT_STATE& boop::ControllerManager::GetCurrentState() const
{
	if (m_IsControllerStateOneCurrent)
	{
		return m_ControllerStateOne;
	}
	return m_ControllerStateTwo;
}
const XINPUT_STATE& boop::ControllerManager::GetPreviousState() const
{
	if (m_IsControllerStateOneCurrent)
	{
		return m_ControllerStateTwo;
	}
	return m_ControllerStateOne;
}
