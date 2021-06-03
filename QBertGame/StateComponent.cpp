#include "StateComponent.h"
#include "JumpComponent.h"
#include <iostream>

StateComponent::StateComponent()
	: m_CurrentState(State::standing),
	m_pMyJumpComponent(nullptr)
{
	//if (m_pOwner != nullptr)
	//	SetJumpComponent(m_pOwner->GetComponentOfType<JumpComponent>());

	//if (m_pMyJumpComponent == nullptr)
	//{
	//	std::cerr << "StateComponent could not find a JumpComponent, it will need to be set!\n";
	//}
}

void StateComponent::Update()
{
	if (m_pMyJumpComponent == nullptr) // Needed for any work to be done
		return;
	
	if (m_CurrentState == State::jumping)
	{
		if (m_pMyJumpComponent->IsJumpDone())
		{
			m_CurrentState = State::standing;
		}
	}
}

bool StateComponent::IsStateEqualTo(const State& state) const
{
	return m_CurrentState == state;
}

void StateComponent::SetJumpComponent(JumpComponent* jumper)
{
	if (jumper != nullptr)
	{
		m_pMyJumpComponent = jumper;
	}
}

bool StateComponent::CanJump() const
{
	return m_CurrentState == State::standing;
}

bool StateComponent::GoJump()
{
	if (CanJump())
	{
		m_CurrentState = State::jumping;
		return true;
	}
	return false;
}
