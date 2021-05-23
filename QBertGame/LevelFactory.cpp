#include "LevelFactory.h"
#include <string>
#include <Scene.h>
#include "TileFactory.h"


using namespace boop;

std::vector<std::shared_ptr<GameObject>> LevelFactory::MakeLevel(Scene& scene, const glm::vec2& levelCenterPos, int levelNumber, int size, bool isTriangle)
{
	const std::string walkedTexturePath = "walked_level" + std::to_string(levelNumber) + ".png";
	const std::string unwalkedTexturePath = "un" + walkedTexturePath;

	const float horizontalStep = m_TileSize / 2;
	const float verticalStep = m_TileSize * 0.75f;
	const float halfPyramidSize = GetPyramidHeight(size) / 2;
	
	glm::vec2 tilePos = { levelCenterPos.x, levelCenterPos.y - halfPyramidSize };
	
	std::vector<std::shared_ptr<GameObject>> tiles = std::vector<std::shared_ptr<GameObject>>{};
	
	for (int row = 0; row < size; row++)
	{
		int colsToMake = size;
		if (isTriangle)
			colsToMake -= row;

		const glm::vec2 rowStartPos = tilePos;
		
		for (int col = 0; col < colsToMake; col++)
		{
			std::shared_ptr<GameObject> tile = TileFactory::MakeTile(
				unwalkedTexturePath, 
				walkedTexturePath, 
				tilePos.x, 
				tilePos.y, 
				m_TileSize, 
				col, 
				row);
			
			tiles.push_back(tile);
			scene.Add(tile);

			// increment pos to down right
			tilePos.x += horizontalStep;
			tilePos.y += verticalStep;
		}

		// increment row and shift tiles to bottom left
		tilePos.x = rowStartPos.x - horizontalStep;
		tilePos.y = rowStartPos.y + verticalStep;
	}

	return tiles;
}

void LevelFactory::LinkTiles(std::vector<std::shared_ptr<boop::GameObject>>& levelTiles)
{
	for (auto& tile : levelTiles)
	{
		LinkTile(tile->GetComponentOfType<TileComponent>(), levelTiles);
	}
}

void LevelFactory::LinkTile(TileComponent* tile, const std::vector<std::shared_ptr<boop::GameObject>>& levelTiles)
{
	int row = tile->GetRow();
	int col = tile->GetColumn();
	
}

float LevelFactory::GetPyramidHeight(int size)
{
	float pyramidHeight = m_TileSize;
	if (size > 1)
	{
		pyramidHeight += m_TileSize;
	}
	if (size - 2 > 0)
	{
		const int middleRowCount = size - 2;
		pyramidHeight += (m_TileSize / 2) * middleRowCount;
	}
	return pyramidHeight;
}
