#pragma once
#include "Command.h"

namespace boop
{
	class PlayerComponent;
	
	class DieCommand final : public Command
	{
	public:
		explicit DieCommand(PlayerComponent* pPlayer);
		void Execute() override;

	private:
		PlayerComponent* m_pPlayer;
	};
}

