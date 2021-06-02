#include "LevelComponent.h"

#include <utility>

/*

** LEVEL LAYOUT **

	  col
		0     1     2     3     4
row  +-----+-----+-----+-----+-----+
	 |     |     |     |     |     |
  0  |  0  |  1  |  2  |  3  |  4  |<----- (4,0)
	 |     |     |     |     |     |
	 +-----+-----+-----+-----+-----+
	 |     |     |     |     |
  1  |  5  |  6  |  7  |  8  |
	 |     |     |     |     |
	 +-----+-----+-----+-----+
	 |     |     |     |
  2  |  9  |  10 |  11 |
	 |     |     |     |
	 +-----+-----+-----+
	 |     |     |
  3  |  12 |  13 |
	 |     |     |
	 +-----+-----+
	 |     |
  4  |  14 |<----- (0,4)
	 |     |
	 +-----+
 */

LevelComponent::LevelComponent(std::vector<std::shared_ptr<boop::GameObject>> levelTiles, int levelSize)
	: m_LevelTiles(std::move(levelTiles))
	, m_LevelSize(levelSize)
{
}

bool LevelComponent::IsCoordinateInBounds(const glm::ivec2& coordinate) const
{
	if (coordinate.x < 0 || coordinate.y < 0)
	{
		return false;
	}

	const int highestCoordinateAllowed = m_LevelSize - 1;
	const int maxColAllowed = highestCoordinateAllowed - coordinate.y;
	const int maxRowAllowed = highestCoordinateAllowed - coordinate.x;

	if (coordinate.x > maxColAllowed || coordinate.y > maxRowAllowed)
	{
		return false;
	}

	return true;
}

TileComponent* LevelComponent::GetTileWithCoordinate(const glm::ivec2& coordinate)
{
	if (!IsCoordinateInBounds(coordinate))
	{
		return nullptr;
	}

	int index = coordinate.x;
	for (int row = 0; row < coordinate.y; row++)
	{
		index += m_LevelSize - row; // -row cause rows get shorter as you go along the triangle
	}

	return m_LevelTiles[index]->GetComponentOfType<TileComponent>();
}
