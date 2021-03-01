#pragma once
#include "DeviceManager.h"

namespace boop
{
	class KeyboardManager : public DeviceManager
	{
		bool ProcessInput() override;
		[[nodiscard]] KeyState GetKeyState(const KeyInfo& keyInfo) const override;
	};
}


