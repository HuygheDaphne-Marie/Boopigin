#include "TumbleMovementComponent.h"
#include "StateComponent.h"
#include <random>
#include <functional>

TumbleMovementComponent::TumbleMovementComponent(TileComponent* startTile, LevelComponent* level, JumpComponent* jumper, StateComponent* state)
	: MovementComponent({ startTile->GetColumn(), startTile->GetRow() }, level, jumper)
	, m_pState(state)
{
}

void TumbleMovementComponent::Update()
{
	//if (m_pState->CanJump())
	//{
	//	auto gen = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());
	//	const bool goDownLeft = gen();

	//	if (goDownLeft)
	//	{
	//		MoveDown();
	//	}
	//	else
	//	{
	//		MoveRight();
	//	}
	//}
}
