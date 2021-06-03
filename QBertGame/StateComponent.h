#pragma once
#include <Component.h>
class JumpComponent;

enum class State
{
	standing,
	jumping
};

class StateComponent : public boop::Component
{
public:
	StateComponent();
	
	void Update() override;

	bool IsStateEqualTo(const State& state) const;

	void SetJumpComponent(JumpComponent* jumper);

	bool CanJump() const;
	bool GoJump();

private:
	State m_CurrentState;
	JumpComponent* m_pMyJumpComponent;
};

