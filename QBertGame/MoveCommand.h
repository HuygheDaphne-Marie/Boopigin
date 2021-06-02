#pragma once
#include <Command.h>
#include "PlayerMovementComponent.h"

class MoveCommand final : public boop::Command
{
public:
	explicit MoveCommand(PlayerMovementComponent* player, Direction direction);
	void Execute() override;

private:
	PlayerMovementComponent* m_pPlayer;
	Direction m_MoveDirection;
};

