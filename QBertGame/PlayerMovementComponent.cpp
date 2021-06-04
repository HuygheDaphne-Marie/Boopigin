#include "PlayerMovementComponent.h"
#include "MoveCommand.h"
#include <InputManager.h>
#include <Timer.h>

#include "StateComponent.h"

PlayerMovementComponent::PlayerMovementComponent(TileComponent* startTile, LevelComponent* level, JumpComponent* jumper,
                                                 std::vector<boop::KeyInfo>& keys)
	: MovementComponent({ startTile->GetColumn(), startTile->GetRow() }, level, jumper)
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

	m_DoFlip = true;
	m_DoGainScore = true;
	
	EventQueue::GetInstance().Subscribe("NewLevelLoaded", this);
	EventQueue::GetInstance().Subscribe("JumpCompleted", this);
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

bool PlayerMovementComponent::OnEvent(const Event& event)
{
	if (event.message == "NewLevelLoaded")
	{
		auto* myState = m_pOwner->GetComponentOfType<StateComponent>();
		myState->ResetState();
		auto* myTexture = m_pOwner->GetComponentOfType<boop::TextureComponent>();

		const glm::ivec2 newTileCoordinate = { 0,0 };
		const glm::vec2 newPos = GetTileStandPosition(m_pLevel->GetTileWithCoordinate(newTileCoordinate), myTexture);
		m_pJumper->SetStartPos(newPos);
		m_CurrentPos = newTileCoordinate;
		
		return true;
	}
	if (event.message == "JumpCompleted")
	{
		if (!m_pLevel->IsCoordinateInBounds(m_CurrentPos))
		{
			EventQueue::GetInstance().Broadcast(new Event("PlayerTakeDamage", m_pOwner));
			return true;
		}
	}
	
	// Pass event on to base
	return MovementComponent::OnEvent(event);
}
