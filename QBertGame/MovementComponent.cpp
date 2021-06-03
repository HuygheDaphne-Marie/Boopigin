#include "MovementComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

MovementComponent::MovementComponent(TileComponent* startTile, LevelComponent* level, JumpComponent* jumper)
	: m_pCurrentTile(startTile)
	, m_pLevel(level)
	, m_pJumper(jumper)
{
	const glm::vec2 pos = GetTileStandPosition(m_pCurrentTile);
	m_pJumper->SetStartPos(pos);
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

glm::vec2 MovementComponent::GetTileStandPosition(TileComponent* tile)
{
	const glm::vec3 position = tile->GetOwner()->GetComponentOfType<boop::TransformComponent>()->GetPosition();
	return { position.x, position.y }; // Todo: will need to move this a bit to get the center of the tile 
}
