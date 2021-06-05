#include "ChaseQbertBehavior.h"

#include "BehaviorMovementComponent.h"
#include "ControlledMovementComponent.h"
#include "StateComponent.h"

ChaseQbertBehavior::ChaseQbertBehavior(LevelComponent* level)
	: m_pLevel(level)
{
}

void ChaseQbertBehavior::Update(BehaviorMovementComponent* movement, StateComponent* state)
{
	if (!state->CanJump())
		return;

	const glm::ivec2 myPos = movement->GetCurrentPosition();
	const std::shared_ptr<boop::GameObject> qbert = m_pLevel->GetQbertClosestTo(myPos);
	if (qbert == nullptr)
		return;

	const glm::ivec2 qbertPos = qbert->GetComponentOfType<ControlledMovementComponent>()->GetCurrentPosition();
	const glm::ivec2 posDelta = qbertPos - myPos;
	if (posDelta.x < 0)
	{
		movement->MoveLeft();
	}
	if (posDelta.y < 0)
	{
		movement->MoveUp();
	}
	if (posDelta.x > 0)
	{
		movement->MoveRight();
	}
	if (posDelta.y > 0)
	{
		movement->MoveDown();
	}
}
