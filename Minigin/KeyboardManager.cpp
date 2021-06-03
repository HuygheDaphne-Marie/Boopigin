#include "MiniginPCH.h"
#include "KeyboardManager.h"

bool boop::KeyboardManager::ProcessInput()
{
	m_FirstKeysIsCurrent = !m_FirstKeysIsCurrent;
	GetCurrentPressedKeys().clear();
	
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}

		if (e.type == SDL_KEYDOWN)
		{
			GetCurrentPressedKeys().push_back(e.key.keysym.sym);
		}
	}

	return true;
}

boop::KeyState boop::KeyboardManager::GetKeyState(const KeyInfo& keyInfo) const
{
	if (keyInfo.type != KeyType::Keyboard)
	{
		return KeyState::BAD_INPUT;
	}

	if (WasPressed(keyInfo.keycode))
	{
		if (IsPressed(keyInfo.keycode))
		{
			return KeyState::Held;
		}

		return KeyState::Released;
	}

	if (IsPressed(keyInfo.keycode))
	{
		return KeyState::Pressed;
	}

	return KeyState::Idle;
}

std::vector<SDL_Keycode>& boop::KeyboardManager::GetCurrentPressedKeys()
{
	if (m_FirstKeysIsCurrent)
	{
		return m_FirstPressedKeys;
	}
	return m_SecondPressedKeys;
}
const std::vector<SDL_Keycode>& boop::KeyboardManager::GetCurrentPressedKeys() const
{
	if (m_FirstKeysIsCurrent)
	{
		return m_FirstPressedKeys;
	}
	return m_SecondPressedKeys;
}
const std::vector<SDL_Keycode>& boop::KeyboardManager::GetPreviousPressedKeys() const
{
	if (m_FirstKeysIsCurrent)
	{
		return m_SecondPressedKeys;
	}
	return m_FirstPressedKeys;
}

bool boop::KeyboardManager::WasPressed(const SDL_Keycode& keycode) const
{
	return Pressed(keycode, GetPreviousPressedKeys());
}
bool boop::KeyboardManager::IsPressed(const SDL_Keycode& keycode) const
{
	return Pressed(keycode, GetCurrentPressedKeys());
}

bool boop::KeyboardManager::Pressed(const SDL_Keycode& keycode, const std::vector<SDL_Keycode>& keysToCheck) const
{
	const auto findItr = std::find(keysToCheck.begin(), keysToCheck.end(), keycode);
	return findItr != keysToCheck.end();
}
