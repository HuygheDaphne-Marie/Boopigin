#include "TumbleBehavior.h"
#include <cstdlib>
#include "BehaviorMovementComponent.h"
#include "StateComponent.h"

void TumbleBehavior::Update(BehaviorMovementComponent* movement, StateComponent* state)
{
	if (state->CanJump())
	{
		if (movement->GetLevel()->IsCoordinateInBounds(movement->GetCurrentPosition()))
		{
			const int randomInt = rand() % 2;
			const bool goDownLeft = (randomInt == 1) ? true : false;

			if (goDownLeft)
				movement->MoveDown();
			else
				movement->MoveRight();
		}
		else
		{
			movement->GetOwner()->MarkForDelete();
		}
	}
}

void TumbleBehavior::Setup(BehaviorMovementComponent* movement, StateComponent* state)
{
	movement->m_DoUnFlip = true;
	state->ResetState(); // it has to do something
}
