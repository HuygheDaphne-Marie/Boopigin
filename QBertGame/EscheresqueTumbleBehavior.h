#pragma once
#include "IMovementBehavior.h"
class EscheresqueTumbleBehavior final : public IMovementBehavior
{
public:
	explicit EscheresqueTumbleBehavior(bool isStandingOnLeftTileSides = true);
	void Update(BehaviorMovementComponent* movement, StateComponent* state) override;

private:
	const bool m_FallsOffOnRight;
};

