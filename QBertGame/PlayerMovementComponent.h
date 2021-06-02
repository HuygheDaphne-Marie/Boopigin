#pragma once
#include "MovementComponent.h"
class MoveCommand;
#include <Key.h>

class PlayerMovementComponent final : public MovementComponent
{
public:
	PlayerMovementComponent(TileComponent* startTile, LevelComponent* level, boop::TransformComponent* myTransform, 
		std::vector<boop::KeyInfo>& keys);
	PlayerMovementComponent(PlayerMovementComponent&) = delete;
	PlayerMovementComponent(PlayerMovementComponent&&) = delete;
	PlayerMovementComponent operator=(PlayerMovementComponent&) = delete;
	PlayerMovementComponent operator=(PlayerMovementComponent&&) = delete;
	~PlayerMovementComponent();

	bool Move(Direction movementDirection) override;

	void Update() override;

private:
	std::vector<MoveCommand*> m_MoveCommands{};
	bool m_CanMove;
	const float m_MoveDelay;
	float m_MoveTimer;
};

