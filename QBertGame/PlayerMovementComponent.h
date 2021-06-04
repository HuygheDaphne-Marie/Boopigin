#pragma once
#include "MovementComponent.h"
class MoveCommand;
#include <Key.h>
#include <IEventListener.h>
#include <EventQueue.h>

class PlayerMovementComponent final : public MovementComponent//, public IEventListener
{
public:
	PlayerMovementComponent(TileComponent* startTile, LevelComponent* level, JumpComponent* jumper, std::vector<boop::KeyInfo>& keys);
	PlayerMovementComponent(PlayerMovementComponent&) = delete;
	PlayerMovementComponent(PlayerMovementComponent&&) = delete;
	PlayerMovementComponent operator=(PlayerMovementComponent&) = delete;
	PlayerMovementComponent operator=(PlayerMovementComponent&&) = delete;
	~PlayerMovementComponent();

	bool Move(Direction movementDirection) override;

	bool OnEvent(const Event& event) override;

private:
	std::vector<MoveCommand*> m_MoveCommands{};

	void Reset();
};

