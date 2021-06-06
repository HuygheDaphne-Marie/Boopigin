#include "MiniginPCH.h"
#include "InputManager.h"
#include "Command.h"
#include "Scene.h"

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
void boop::InputManager::HandleInput()
{
	//auto commands = GetCommandsActiveScene();
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
	//auto commands = GetCommandsActiveScene();
	CommandInfo info = { neededKeyState, pCommand };
	return m_Commands.insert({ keyInfo, info }).second;
}

void boop::InputManager::RemoveCommand(Command* pCommand)
{
	// Won't work, can't figure out why
	//const auto itr = std::remove_if(commands.begin(), commands.end(), 
	//	[pCommand](const std::pair<KeyInfo, CommandInfo>& pair)
	//	{
	//		return pair.second.pCommand == pCommand;
	//    }
	//);
	//commands.erase(itr);
	//auto commands = GetCommandsActiveScene();

	const KeyInfo* pKey = nullptr;
	for (auto& pair : m_Commands)
	{
		if (pair.second.pCommand == pCommand)
		{
			pKey = &pair.first;
			break;
		}
	}

	if (pKey != nullptr)
	{
		m_Commands.erase(*pKey);
	}
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

/*
std::unordered_map<boop::KeyInfo, boop::CommandInfo, boop::KeyInfoHasher>& boop::InputManager::GetCommandsActiveScene()
{
	const auto activeScene = boop::SceneManager::GetInstance().GetActiveScene();
	return GetCommandsForScene(activeScene);
}
std::unordered_map<boop::KeyInfo, boop::CommandInfo, boop::KeyInfoHasher>& boop::InputManager::GetCommandsForScene(std::shared_ptr<Scene> scene)
{
	const auto findItr = m_CommandsByScene.find(scene->GetId());
	if (findItr == m_CommandsByScene.end())
	{
		m_CommandsByScene[scene->GetId()] = std::unordered_map<boop::KeyInfo, boop::CommandInfo, boop::KeyInfoHasher>{};
	}

	return m_CommandsByScene[scene->GetId()];
}
*/
