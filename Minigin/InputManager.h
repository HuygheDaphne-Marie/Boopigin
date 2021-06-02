#pragma once
#include "Singleton.h"
#include <unordered_map>

#include "Key.h"
#include "ControllerManager.h"
#include "KeyboardManager.h"

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
		void RemoveCommand(Command* pCommand);

	private:
		friend class Singleton<InputManager>;
		InputManager();

		[[nodiscard]] KeyState GetKeyStateFromDevice(KeyInfo keyInfo) const;
		
		std::unordered_map<KeyInfo, CommandInfo, KeyInfoHasher> m_Commands{};

		//Todo: Should get rid of superclass, make ControllerManager actually handle multiple controllers
		ControllerManager m_Controller;
		KeyboardManager m_Keyboard;
		//Todo: Add Keyboard & Mouse managers, these will only handle one device so they should be easier
		
	};

}

