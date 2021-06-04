#include "TumbleMovementComponent.h"
#include "StateComponent.h"
#include <random>

TumbleMovementComponent::TumbleMovementComponent(TileComponent* startTile, LevelComponent* level, JumpComponent* jumper, StateComponent* state)
	: MovementComponent({ startTile->GetColumn(), startTile->GetRow() }, level, jumper)
	, m_pState(state)
{
}

void TumbleMovementComponent::Update()
{
	MovementComponent::Update();
	if (m_pState->CanJump())
	{
		if (m_pLevel->IsCoordinateInBounds(m_CurrentPos))
		{
			const int randomInt = rand() % 2;
			const bool goDownLeft = (randomInt == 1) ? true : false;

			if (goDownLeft)
				MoveDown();
			else
				MoveRight();
		}
		else
		{
			// todo: reset or die, or whatever
		}
	}
}
