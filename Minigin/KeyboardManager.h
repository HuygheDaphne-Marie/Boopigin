#pragma once
#include <SDL.h>
#include "DeviceManager.h"


namespace boop
{
	class KeyboardManager final : public DeviceManager
	{
	public:
		bool ProcessInput() override;
		[[nodiscard]] KeyState GetKeyState(const KeyInfo& keyInfo) const override;

	private:
		std::vector<SDL_Keycode> m_FirstPressedKeys;
		std::vector<SDL_Keycode> m_SecondPressedKeys;
		bool m_FirstKeysIsCurrent = false; // Set to true on first iteration

		[[nodiscard]] std::vector<SDL_Keycode>& GetCurrentPressedKeys();
		[[nodiscard]] const std::vector<SDL_Keycode>& GetCurrentPressedKeys() const;
		[[nodiscard]] const std::vector<SDL_Keycode>& GetPreviousPressedKeys() const;

		[[nodiscard]] bool WasPressed(const SDL_Keycode& keycode) const;
		[[nodiscard]] bool IsPressed(const SDL_Keycode& keycode) const;
		[[nodiscard]] bool Pressed(const SDL_Keycode& keycode, const std::vector<SDL_Keycode>& keysToCheck) const;
	};
}


