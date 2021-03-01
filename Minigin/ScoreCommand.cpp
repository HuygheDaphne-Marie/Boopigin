#include "MiniginPCH.h"
#include "ScoreCommand.h"

#include "PlayerComponent.h"

boop::ScoreCommand::ScoreCommand(PlayerComponent* pPlayer)
	: m_pPlayer(pPlayer)
{
}

void boop::ScoreCommand::Execute()
{
	m_pPlayer->ScoreGained((25));
}
