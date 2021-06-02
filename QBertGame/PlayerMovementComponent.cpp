#include "PlayerMovementComponent.h"
#include "MoveCommand.h"
#include <InputManager.h>
#include <Timer.h>

PlayerMovementComponent::PlayerMovementComponent(TileComponent* startTile, LevelComponent* level, boop::TransformComponent* myTransform, 
	std::vector<boop::KeyInfo>& keys)
	: MovementComponent(startTile, level, myTransform)
	, m_CanMove(true)
	, m_MoveDelay(1.f)
	, m_MoveTimer(0.f)
{
	m_MoveCommands.resize(4);
	m_MoveCommands[0] = new MoveCommand(this, Direction::up);
	m_MoveCommands[1] = new MoveCommand(this, Direction::right);
	m_MoveCommands[2] = new MoveCommand(this, Direction::down);
	m_MoveCommands[3] = new MoveCommand(this, Direction::left);

	boop::InputManager::GetInstance().AddCommandToButton(
		keys[0], m_MoveCommands[0], boop::KeyState::Pressed);
	boop::InputManager::GetInstance().AddCommandToButton(
		keys[1], m_MoveCommands[1], boop::KeyState::Pressed);
	boop::InputManager::GetInstance().AddCommandToButton(
		keys[2], m_MoveCommands[2], boop::KeyState::Pressed);
	boop::InputManager::GetInstance().AddCommandToButton(
		keys[3], m_MoveCommands[3], boop::KeyState::Pressed);
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
	if (m_CanMove)
	{
		std::cout << "========\n";
		std::cout << "x: " << std::to_string(m_pCurrentTile->GetColumn()) << ", y: " << std::to_string(m_pCurrentTile->GetRow()) << std::endl;
		const bool didMove = MovementComponent::Move(movementDirection);
		std::cout << "x: " << std::to_string(m_pCurrentTile->GetColumn()) << ", y: " << std::to_string(m_pCurrentTile->GetRow()) << std::endl;
		std::cout << "========\n";
		if (didMove)
		{
			m_CanMove = false;
			return true;
		}
	}
	return false;
}

void PlayerMovementComponent::Update()
{
	
	if (!m_CanMove)
	{
		m_MoveTimer += boop::Timer::GetInstance().GetElapsedSec();
		if (m_MoveTimer >= m_MoveDelay)
		{
			m_MoveTimer = 0;
			m_CanMove = true;
		}
	}
}
