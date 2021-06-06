#include "QuadDirectionalJumpAnimationComponent.h"
#include "ControlledMovementComponent.h"
#include "BehaviorMovementComponent.h"

QuadDirectionalJumpAnimationComponent::QuadDirectionalJumpAnimationComponent(const std::string& texturePath, int frameWidth,
	int frameHeight, int displayWidth, int displayHeight)
	: AnimationComponent(texturePath, frameWidth, frameHeight, displayWidth, displayHeight)
	, m_pState(nullptr)
	, m_pMovement(nullptr)
{
}

void QuadDirectionalJumpAnimationComponent::Startup()
{
	AnimationComponent::Startup();
	
	m_pState = m_pOwner->GetComponentOfType<StateComponent>();
	m_pMovement = m_pOwner->GetComponentOfType<MovementComponent>();
	
	m_pOwner->AddTag("quadAnimation");
}

void QuadDirectionalJumpAnimationComponent::Update()
{	
	if (m_pState == nullptr || m_pMovement == nullptr)
		return;

	int frame = GetFrameFromDirection(m_pMovement->GetLastMovedInDirection());
	if (m_pState->IsStateEqualTo(State::jumping))
		frame++;

	if (GetCurrentFrame() != static_cast<unsigned int>(frame))
		SetFrame(frame);
}

int QuadDirectionalJumpAnimationComponent::GetFrameFromDirection(const Direction direction)
{
	switch (direction)
	{
	case Direction::up:
		return 0;
	case Direction::down:
		return 6;

	case Direction::escheresqueLeft:
	case Direction::left:
		return 2;

	case Direction::escheresqueRight:
	case Direction::right:
	default: 
		return 4;
	}
}
