#include "MovementComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

MovementComponent::MovementComponent(TileComponent* startTile, LevelComponent* level, boop::TransformComponent* myTransform)
	: m_pCurrentTile(startTile)
	, m_pLevel(level)
	, m_pTransform(myTransform)
{
	const glm::vec2 pos = GetTileStandPosition(m_pCurrentTile);
	m_pTransform->SetPosition(pos.x, pos.y);
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
	
	if (m_pLevel->IsCoordinateInBounds(newTileCoordinate))
	{
		TileComponent* newTile = m_pLevel->GetTileWithCoordinate(newTileCoordinate);
		m_pCurrentTile = newTile;
		m_pCurrentTile->OnWalked();
		const glm::vec2 newPos = GetTileStandPosition(m_pCurrentTile);
		m_pTransform->SetPosition(newPos.x, newPos.y);
		
		// Todo: (later that will be nicely animated with a leap)
		return true;
	}
	//else
	//{
	//	// check if there's a teleporter there
	//	// 
	//	// if not, jump into empty space & die
	//}
	return false;
}

glm::vec2 MovementComponent::GetTileStandPosition(TileComponent* tile)
{
	const glm::vec3 position = tile->GetOwner()->GetComponentOfType<boop::TransformComponent>()->GetPosition();
	return { position.x, position.y }; // Todo: will need to move this a bit to get the center of the tile 
}
