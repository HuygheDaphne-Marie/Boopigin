#include "JumpComponent.h"
#include <Timer.h>
#include "StateComponent.h"

JumpComponent::JumpComponent(boop::TransformComponent* myTransform, StateComponent* myState, float desiredLeapTime)
	: m_pTransform(myTransform)
	, m_StartPos(0,0)
	, m_EndPos(0,0)
	, m_CurrentPos(0,0)
	, m_LeapDuration(desiredLeapTime)
	, m_LeapTimer(0.f)
	, m_pState(myState)
{
	m_pState->SetJumpComponent(this);
}

void JumpComponent::SetStartPos(const glm::vec2& pos)
{
	m_StartPos = pos;
	m_pTransform->SetPosition(pos.x, pos.y);
}
void JumpComponent::SetEndPos(const glm::vec2& pos)
{
	m_EndPos = pos;
}

bool JumpComponent::StartJump(const glm::vec2& end)
{
	if (m_pState->CanJump())
	{
		SetEndPos(end);
		return m_pState->GoJump();
	}
	return false;
}

bool JumpComponent::IsJumpDone() const
{
	if (m_pState->IsStateEqualTo(State::jumping))
	{
		if (m_StartPos == m_EndPos)
		{
			return true;
		}
		return false;
	}
	return true;
}

void JumpComponent::Update()
{
	if (m_pState->IsStateEqualTo(State::jumping))
	{
		m_LeapTimer += boop::Timer::GetInstance().GetElapsedSec();
		
		const float fractionOfLeapCompleted = m_LeapTimer / m_LeapDuration;
		const glm::vec2 jumpDirection = m_EndPos - m_StartPos;	
		m_CurrentPos = m_StartPos + (jumpDirection * fractionOfLeapCompleted);

		if(fractionOfLeapCompleted < 1.f)
		{
			m_pTransform->SetPosition(m_CurrentPos.x, m_CurrentPos.y);
		}
		else
		{
			SetStartPos(m_EndPos);
			m_LeapTimer = 0.f;
		}
	}
}
