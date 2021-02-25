#include "MiniginPCH.h"
#include "DieCommand.h"
#include "PlayerComponent.h"

boop::DieCommand::DieCommand(PlayerComponent* pPlayer)
	: m_pPlayer(pPlayer)
{
}

void boop::DieCommand::Execute()
{
	std::cout << "Died!\n";
	m_pPlayer->OnDeath();
}
