#include "ControlledMovementComponent.h"
#include "MoveCommand.h"
#include <InputManager.h>
#include <Timer.h>

#include "StateComponent.h"

ControlledMovementComponent::ControlledMovementComponent(TileComponent* startTile, LevelComponent* level, JumpComponent* jumper,
                                                 std::vector<boop::KeyInfo>& keys)
	: MovementComponent({ startTile->GetColumn(), startTile->GetRow() }, level, jumper)
	, m_SpawnPos({ startTile->GetColumn(), startTile->GetRow() })
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
	EventQueue::GetInstance().Subscribe("PlayerTakeDamage", this);
}

ControlledMovementComponent::~ControlledMovementComponent()
{
	boop::InputManager& inputManager = boop::InputManager::GetInstance();
	for (auto& command : m_MoveCommands)
	{
		inputManager.RemoveCommand(command);
		delete command;
	}
}

void ControlledMovementComponent::Startup()
{
	m_pOwner->AddTag("controlled");
	MovementComponent::Startup();
}

bool ControlledMovementComponent::Move(Direction movementDirection)
{
	return MovementComponent::Move(movementDirection);
}

bool ControlledMovementComponent::OnEvent(const Event& event)
{
	if (event.message == "NewLevelLoaded")
	{
		Reset();
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
	if (event.message == "PlayerTakeDamage")
	{
		Reset();
		return true;
	}
	
	// Pass event on to base
	return MovementComponent::OnEvent(event);
}

void ControlledMovementComponent::Reset()
{
	auto* myState = m_pOwner->GetComponentOfType<StateComponent>();
	myState->ResetState();
	SetPosition(m_SpawnPos);
	m_CurrentPos = m_SpawnPos;
}
