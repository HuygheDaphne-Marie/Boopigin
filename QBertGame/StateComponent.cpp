#include "StateComponent.h"
#include "JumpComponent.h"
#include <iostream>
#include <Timer.h>

StateComponent::StateComponent()
	: m_JumpCooldownTime(0.f),
	m_CurrentState(State::standing),
	m_pMyJumpComponent(nullptr),
	m_JumpCooldownTimer(0.f)
{
}

void StateComponent::Update()
{
	if (m_pMyJumpComponent == nullptr) // Needed for any work to be done
		return;

	if (m_CurrentState == State::standing)
	{
		m_JumpCooldownTimer += boop::Timer::GetInstance().GetElapsedSec();
	}
	
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
	return m_CurrentState == State::standing && m_JumpCooldownTimer > m_JumpCooldownTime;
}

bool StateComponent::GoJump()
{
	if (CanJump())
	{
		m_CurrentState = State::jumping;
		m_JumpCooldownTimer = 0.f;
		return true;
	}
	return false;
}

void StateComponent::ResetState()
{
	m_CurrentState = State::standing;
}
