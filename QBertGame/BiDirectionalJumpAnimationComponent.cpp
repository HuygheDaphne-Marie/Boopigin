#include "BiDirectionalJumpAnimationComponent.h"

BiDirectionalJumpAnimationComponent::BiDirectionalJumpAnimationComponent(const std::string& texturePath, int frameWidth,
	int frameHeight, int displayWidth, int displayHeight)
	: AnimationComponent(texturePath, frameWidth, frameHeight, displayWidth, displayHeight)
	, m_pState(nullptr)
	, m_pMovement(nullptr)
{
}

void BiDirectionalJumpAnimationComponent::Startup()
{
	AnimationComponent::Startup();

	m_pState = m_pOwner->GetComponentOfType<StateComponent>();
	m_pMovement = m_pOwner->GetComponentOfType<MovementComponent>();

	m_pOwner->AddTag("biAnimation");
}

void BiDirectionalJumpAnimationComponent::Update()
{
	if (m_pState == nullptr || m_pMovement == nullptr)
		return;

	int frame = GetFrameFromDirection(m_pMovement->GetLastMovedInDirection());
	if (m_pState->IsStateEqualTo(State::jumping))
		frame++;

	if (GetCurrentFrame() != static_cast<unsigned int>(frame))
		SetFrame(frame);
}

int BiDirectionalJumpAnimationComponent::GetFrameFromDirection(const Direction direction)
{
	switch (direction)
	{
	case Direction::escheresqueLeft:
	case Direction::down:
		return 0;

	case Direction::escheresqueRight:
	case Direction::right:
	default:
		return 2;
	}
}