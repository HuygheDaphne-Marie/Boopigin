#pragma once
#include "MovementComponent.h"
#include "IMovementBehavior.h"
class BehaviorMovementComponent final : public MovementComponent
{
public:
	BehaviorMovementComponent(TileComponent* startTile, LevelComponent* level, JumpComponent* jumper,
		StateComponent* state, IMovementBehavior* myBehavior);
	BehaviorMovementComponent(BehaviorMovementComponent&) = delete;
	BehaviorMovementComponent(BehaviorMovementComponent&&) = delete;
	BehaviorMovementComponent operator=(BehaviorMovementComponent&) = delete;
	BehaviorMovementComponent operator=(BehaviorMovementComponent&&) = delete;
	~BehaviorMovementComponent();
	
	void Update() override;

private:
	friend class IMovementBehavior;
	StateComponent* m_pState;
	IMovementBehavior* m_pBehavior;
};

