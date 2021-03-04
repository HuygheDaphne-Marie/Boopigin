#include "MiniginPCH.h"
#include "InputManager.h"
#include "Command.h"

boop::InputManager::InputManager()
	: m_Controller(0)
{
}

bool boop::InputManager::ProcessInput()
{
	bool shouldContinue = true; // Todo: make this better later, we might get exit commands from more than just one source
	shouldContinue = m_Keyboard.ProcessInput();
	m_Controller.ProcessInput();

	return shouldContinue;
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
		return m_Keyboard.GetKeyState(keyInfo);
	case KeyType::XInputController: 
		return m_Controller.GetKeyState(keyInfo);
	default: 
		return KeyState::BAD_INPUT;
	}
}
