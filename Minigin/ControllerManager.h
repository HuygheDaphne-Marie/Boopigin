#pragma once
#include "DeviceManager.h"
class ControllerManager final : public DeviceManager
{
public:
	ControllerManager(int controllerId);
	
	bool ProcessInput();
	[[nodiscard]] KeyState GetButtonState(ControllerButton button) const;

private:
	
	[[nodiscard]] bool IsPressed(ControllerButton button) const;
	[[nodiscard]] bool WasPressed(ControllerButton button) const;
	[[nodiscard]] bool Pressed(ControllerButton button, const std::vector<XINPUT_STATE>& stateToUse) const;

	int m_ControllerId;

	XINPUT_STATE m_PreviousControllerStates;
	XINPUT_STATE m_CurrentControllerStates;
};

