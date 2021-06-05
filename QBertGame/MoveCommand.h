#pragma once
#include <Command.h>
#include "ControlledMovementComponent.h"

class MoveCommand final : public boop::Command
{
public:
	explicit MoveCommand(ControlledMovementComponent* player, Direction direction);
	void Execute() override;

private:
	ControlledMovementComponent* m_pPlayer;
	Direction m_MoveDirection;
};

