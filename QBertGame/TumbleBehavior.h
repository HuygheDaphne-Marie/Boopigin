#pragma once
#include "IMovementBehavior.h"
class TumbleBehavior final : public IMovementBehavior
{
public:
	void Update(BehaviorMovementComponent* movement, StateComponent* state) override;
};

