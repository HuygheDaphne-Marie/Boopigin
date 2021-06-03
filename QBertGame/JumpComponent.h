#pragma once
#include <Component.h>
#include <TransformComponent.h>
class StateComponent;

class JumpComponent : public boop::Component
{
public:
	JumpComponent(boop::TransformComponent* myTransform, StateComponent* myState, float desiredLeapTime);

	void SetStartPos(const glm::vec2& pos);
	void SetEndPos(const glm::vec2& pos);
	bool StartJump(const glm::vec2& end);

	bool IsJumpDone() const;
	
	void Update() override;

private:
	boop::TransformComponent* m_pTransform;
	
	glm::vec2 m_StartPos;
	glm::vec2 m_EndPos;
	glm::vec2 m_CurrentPos;
	const float m_LeapDuration;
	float m_LeapTimer;

	StateComponent* m_pState;
};

