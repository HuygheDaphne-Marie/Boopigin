#pragma once
#include "DeviceManager.h"

namespace boop
{
	class ControllerManager final : public DeviceManager
	{
	public:
		explicit ControllerManager(int controllerId);
		
		bool ProcessInput() override;
		[[nodiscard]] KeyState GetKeyState(const KeyInfo& keyInfo) const override;

	private:
		
		[[nodiscard]] bool IsPressed(ControllerButton button) const;
		[[nodiscard]] bool WasPressed(ControllerButton button) const;
		[[nodiscard]] bool Pressed(ControllerButton button, const XINPUT_STATE& stateToUse) const;

		[[nodiscard]] XINPUT_STATE& GetCurrentState();
		[[nodiscard]] XINPUT_STATE& GetPreviousState();
		[[nodiscard]] const XINPUT_STATE& GetCurrentState() const;
		[[nodiscard]] const XINPUT_STATE& GetPreviousState() const;

		int m_ControllerId;
		bool m_IsControllerStateOneCurrent;
		
		XINPUT_STATE m_ControllerStateOne;
		XINPUT_STATE m_ControllerStateTwo;
	};
}

