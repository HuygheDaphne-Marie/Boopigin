#pragma once
#include "Key.h"

namespace boop
{
	class DeviceManager 
	{
	public:
		virtual ~DeviceManager() = default;

		virtual bool ProcessInput() = 0;
		[[nodiscard]] virtual KeyState GetKeyState(const KeyInfo& keyInfo) const = 0;
	};
}

