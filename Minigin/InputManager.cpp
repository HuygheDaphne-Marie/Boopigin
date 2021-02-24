#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Command.h"

boop::InputManager::InputManager()
	: m_Controller(0)
{
}

bool boop::InputManager::ProcessInput()
{
	m_Controller.ProcessInput();
	
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
	for (const auto& pair : m_Commands)
	{
		if (GetKeyStateFromDevice(pair.first) == pair.second.KeyStateNeeded)
		{
			pair.second.pCommand->Execute();
		}
	}
}

bool boop::InputManager::AddCommandToButton(KeyInfo keyInfo, Command* pCommand, KeyState neededKeyState)
{
	CommandInfo info = { neededKeyState, pCommand };
	return m_Commands.insert({ keyInfo, info }).second;
}



boop::KeyState boop::InputManager::GetKeyStateFromDevice(KeyInfo keyInfo) const
{
	switch (keyInfo.type)
	{
	case KeyType::Keyboard: 
		return KeyState::BAD_INPUT; //Todo: Temp until keyboardManager is added
	case KeyType::XInputController: 
		return m_Controller.GetKeyState(keyInfo);
	default: 
		return KeyState::BAD_INPUT;
	}
}
