#pragma once
#include "MovementComponent.h"
class MoveCommand;
#include <Key.h>
#include <EventQueue.h>

class ControlledMovementComponent final : public MovementComponent//, public IEventListener
{
public:
	ControlledMovementComponent(TileComponent* startTile, LevelComponent* level, JumpComponent* jumper, std::vector<boop::KeyInfo>& keys);
	ControlledMovementComponent(ControlledMovementComponent&) = delete;
	ControlledMovementComponent(ControlledMovementComponent&&) = delete;
	ControlledMovementComponent operator=(ControlledMovementComponent&) = delete;
	ControlledMovementComponent operator=(ControlledMovementComponent&&) = delete;
	~ControlledMovementComponent();

	void Startup() override;
	
	bool Move(Direction movementDirection) override;

	bool OnEvent(const Event& event) override;

private:
	std::vector<MoveCommand*> m_MoveCommands{};

	void Reset();
};

