#include "MovementComponent.h"
#include "LevelFactory.h"
#include <TextureComponent.h>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

MovementComponent::MovementComponent(TileComponent* startTile, LevelComponent* level, JumpComponent* jumper)
	: m_pCurrentTile(startTile)
	, m_pLevel(level)
	, m_pJumper(jumper)
	, m_HasStarted(false)
{
}

void MovementComponent::Update()
{
	if (!m_HasStarted)
	{
		// Dirty fix, but will have to do for now
		const glm::vec2 pos = GetTileStandPosition(m_pCurrentTile);
		m_pJumper->SetStartPos(pos);
		m_HasStarted = true;
	}
}


bool MovementComponent::MoveUp()
{
	return Move(Direction::up);
}
bool MovementComponent::MoveRight()
{
	return Move(Direction::right);
}
bool MovementComponent::MoveDown()
{
	return Move(Direction::down);
}
bool MovementComponent::MoveLeft()
{
	return Move(Direction::left);
}

bool MovementComponent::Move(Direction movementDirection)
{
	glm::ivec2 coordinateChange = { 0, 0 };
	
	switch (movementDirection)
	{
	case Direction::up:
		coordinateChange.y = -1;
		break;
	case Direction::right:
		coordinateChange.x = 1;
		break;
	case Direction::down:
		coordinateChange.y = 1;
		break;
	case Direction::left:
		coordinateChange.x = -1;
		break;
	}

	const glm::ivec2 currentTileCoordinate = { m_pCurrentTile->GetColumn(), m_pCurrentTile->GetRow() };
	const glm::ivec2 newTileCoordinate = currentTileCoordinate + coordinateChange;

	return MoveTo(newTileCoordinate);
}
bool MovementComponent::MoveTo(const glm::ivec2& tileCoordinate)
{
	if (m_pLevel->IsCoordinateInBounds(tileCoordinate))
	{
		TileComponent* newTile = m_pLevel->GetTileWithCoordinate(tileCoordinate);
		const glm::vec2 newPos = GetTileStandPosition(newTile);

		if (m_pJumper->StartJump(newPos))
		{
			m_pCurrentTile = newTile;
			m_pCurrentTile->OnWalked();
			return true;
		}
		return false;
	}
	else
	{
		//if (m_pLevel.DoesCoordinateHaveTeleporter(tileCoordinate))
		//{
		//	
		//}
		
		// if not, jump into empty space & die
	}
	return false;
}

glm::vec2 MovementComponent::GetTileStandPosition(TileComponent* tile) const
{
	auto* texture = m_pOwner->GetComponentOfType<boop::TextureComponent>();
	const auto qbertHeight = static_cast<float>(texture->GetHeight());
	const auto qbertWidth = static_cast<float>(texture->GetWidth());
	
	const float verticalAdjustment = LevelFactory::m_TileSize / 4 - qbertHeight;
	const float horizontalAdjustment = LevelFactory::m_TileSize / 2 - qbertWidth / 2;
	const glm::vec3 position = tile->GetOwner()->GetComponentOfType<boop::TransformComponent>()->GetPosition();
	
	return { position.x + horizontalAdjustment, position.y + verticalAdjustment };
}
