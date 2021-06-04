#pragma once
#include "IMovementBehavior.h"
class TumbleBehavior final : public IMovementBehavior
{
	void Update(BehaviorMovementComponent* movement, StateComponent* state) override;
};

