#include "MiniginPCH.h"
#include "ControllerManager.h"

ControllerManager::ControllerManager(int controllerId)
	: m_ControllerId(controllerId)
	, m_PreviousControllerStates{}
	, m_CurrentControllerStates{}
{
}

bool ControllerManager::ProcessInput()
{
}

KeyState ControllerManager::GetButtonState(ControllerButton button) const
{
}

bool ControllerManager::IsPressed(ControllerButton button) const
{
}

bool ControllerManager::WasPressed(ControllerButton button) const
{
}

bool ControllerManager::Pressed(ControllerButton button, const std::vector<XINPUT_STATE>& stateToUse) const
{
}
