#pragma once
#include "MovementComponent.h"
class TumbleMovementComponent final : public MovementComponent
{
public:
	TumbleMovementComponent(TileComponent* startTile, LevelComponent* level, JumpComponent* jumper, StateComponent* state);

	void Update() override;

private:
	StateComponent* m_pState;
};

