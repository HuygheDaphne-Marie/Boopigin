#pragma once
#include "IMovementBehavior.h"
#include "LevelComponent.h"

class ChaseQbertBehavior final : public IMovementBehavior
{
public:
	explicit ChaseQbertBehavior(LevelComponent* level);
	
	void Setup(BehaviorMovementComponent* movement, StateComponent* state) override;
	void Update(BehaviorMovementComponent* movement, StateComponent* state) override;

private:
	LevelComponent* m_pLevel;
};

