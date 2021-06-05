#include "BehaviorMovementComponent.h"
#include "StateComponent.h"
#include <random>

BehaviorMovementComponent::BehaviorMovementComponent(TileComponent* startTile, LevelComponent* level, JumpComponent* jumper, 
	StateComponent* state, IMovementBehavior* myBehavior)
	: MovementComponent({ startTile->GetColumn(), startTile->GetRow() }, level, jumper)
	, m_pState(state)
	, m_pBehavior(myBehavior)
{
	m_pBehavior->Setup(this, m_pState);
}

BehaviorMovementComponent::~BehaviorMovementComponent()
{
	delete m_pBehavior;
}

void BehaviorMovementComponent::Update()
{
	m_pBehavior->Update(this, m_pState);
}
