#pragma once
class BehaviorMovementComponent;
class StateComponent;

class IMovementBehavior
{
public:
	virtual ~IMovementBehavior() = default;
	virtual void Update(BehaviorMovementComponent* movement, StateComponent* state) = 0;
};
