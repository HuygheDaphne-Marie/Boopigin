#pragma once
#include "Singleton.h"
#include <unordered_map>

#include "Key.h"
#include "ControllerManager.h"

namespace boop
{
	class Command;
	struct CommandInfo
	{
		KeyState KeyStateNeeded;
		Command* pCommand;
	};

	class InputManager final : public Singleton<InputManager> 
	{
	public:
		bool ProcessInput();
		void HandleInput() const;

		bool AddCommandToButton(KeyInfo keyInfo, Command* pCommand, KeyState neededKeyState);

	private:
		friend class Singleton<InputManager>;
		InputManager();

		[[nodiscard]] KeyState GetKeyStateFromDevice(KeyInfo keyInfo) const;
		
		std::unordered_map<KeyInfo, CommandInfo, KeyInfoHasher> m_Commands;

		ControllerManager m_Controller;
		
	};

}

