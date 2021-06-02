#include "MoveCommand.h"

MoveCommand::MoveCommand(PlayerMovementComponent* player, Direction direction)
	: m_pPlayer(player)
	, m_MoveDirection(direction)
{
}

void MoveCommand::Execute()
{
	m_pPlayer->Move(m_MoveDirection);
}
