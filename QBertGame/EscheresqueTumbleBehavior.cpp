#include "EscheresqueTumbleBehavior.h"

#include "BehaviorMovementComponent.h"
#include "StateComponent.h"

EscheresqueTumbleBehavior::EscheresqueTumbleBehavior(bool isStandingOnLeftTileSides)
	: m_FallsOffOnRight(!isStandingOnLeftTileSides)
{
}

void EscheresqueTumbleBehavior::Update(BehaviorMovementComponent* movement, StateComponent* state)
{
	if (state->CanJump())
	{
		if (m_FallsOffOnRight && movement->GetCurrentPosition().x == 0 ||
			!m_FallsOffOnRight && movement->GetCurrentPosition().y == 0)
		{
			// Reached the end of their side of the pyramid, no 'ground' is below anymore
			movement->GetOwner()->MarkForDelete();
		}
		
		if (movement->GetLevel()->IsCoordinateInBounds(movement->GetCurrentPosition()))
		{
			const int randomInt = rand() % 2;
			const bool goUp = (randomInt == 1) ? true : false;

			if (goUp)
				if (m_FallsOffOnRight)
					movement->MoveLeft();
				else
					movement->MoveUp();
			else
				if (m_FallsOffOnRight)
					movement->MoveEscheresqueRight();
				else
					movement->MoveEscheresqueLeft(); 
		}
	}
}
