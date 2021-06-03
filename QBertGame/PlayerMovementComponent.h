#pragma once
#include "MovementComponent.h"
class MoveCommand;
#include <Key.h>


class PlayerMovementComponent final : public MovementComponent
{
public:
	PlayerMovementComponent(TileComponent* startTile, LevelComponent* level, JumpComponent* jumper, std::vector<boop::KeyInfo>& keys);
	PlayerMovementComponent(PlayerMovementComponent&) = delete;
	PlayerMovementComponent(PlayerMovementComponent&&) = delete;
	PlayerMovementComponent operator=(PlayerMovementComponent&) = delete;
	PlayerMovementComponent operator=(PlayerMovementComponent&&) = delete;
	~PlayerMovementComponent();

	bool Move(Direction movementDirection) override;

private:
	std::vector<MoveCommand*> m_MoveCommands{};
};

