#include "PlayerMovementComponent.h"
#include "MoveCommand.h"
#include <InputManager.h>
#include <Timer.h>

PlayerMovementComponent::PlayerMovementComponent(TileComponent* startTile, LevelComponent* level, JumpComponent* jumper,
	std::vector<boop::KeyInfo>& keys)
	: MovementComponent(startTile, level, jumper)
{
	const int upIndex = static_cast<std::underlying_type<Direction>::type>(Direction::up);
	const int rightIndex = static_cast<std::underlying_type<Direction>::type>(Direction::right);
	const int downIndex = static_cast<std::underlying_type<Direction>::type>(Direction::down);
	const int leftIndex = static_cast<std::underlying_type<Direction>::type>(Direction::left);
	
	m_MoveCommands.resize(4);
	m_MoveCommands[upIndex] = new MoveCommand(this, Direction::up);
	m_MoveCommands[rightIndex] = new MoveCommand(this, Direction::right);
	m_MoveCommands[downIndex] = new MoveCommand(this, Direction::down);
	m_MoveCommands[leftIndex] = new MoveCommand(this, Direction::left);

	boop::InputManager::GetInstance().AddCommandToButton(keys[upIndex], m_MoveCommands[upIndex], boop::KeyState::Pressed);
	boop::InputManager::GetInstance().AddCommandToButton(keys[rightIndex], m_MoveCommands[rightIndex], boop::KeyState::Pressed);
	boop::InputManager::GetInstance().AddCommandToButton(keys[downIndex], m_MoveCommands[downIndex], boop::KeyState::Pressed);
	boop::InputManager::GetInstance().AddCommandToButton(keys[leftIndex], m_MoveCommands[leftIndex], boop::KeyState::Pressed);
}

PlayerMovementComponent::~PlayerMovementComponent()
{
	boop::InputManager& inputManager = boop::InputManager::GetInstance();
	for (auto& command : m_MoveCommands)
	{
		inputManager.RemoveCommand(command);
		delete command;
	}
}

bool PlayerMovementComponent::Move(Direction movementDirection)
{
	//std::cout << "========\n";
	//std::cout << "x: " << std::to_string(m_pCurrentTile->GetColumn()) << ", y: " << std::to_string(m_pCurrentTile->GetRow()) << std::endl;
	const bool didMove = MovementComponent::Move(movementDirection);
	//std::cout << "x: " << std::to_string(m_pCurrentTile->GetColumn()) << ", y: " << std::to_string(m_pCurrentTile->GetRow()) << std::endl;
	//std::cout << "========\n";
	return didMove;
}
