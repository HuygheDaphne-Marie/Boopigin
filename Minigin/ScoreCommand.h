#pragma once
#include "Command.h"

namespace boop
{
	class PlayerComponent;
	class ScoreCommand : public Command
	{
	public:
		explicit ScoreCommand(PlayerComponent* pPlayer);
		void Execute() override;

	private:
		PlayerComponent* m_pPlayer;
	};
}


