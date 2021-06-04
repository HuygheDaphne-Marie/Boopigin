#include "LevelFactory.h"
#include <string>
#include <Scene.h>
#include "TileFactory.h"
#include "json.hpp"
#include <fstream>

using namespace boop;
using json = nlohmann::json;

float LevelFactory::m_TileSize = 64.f;
std::string LevelFactory::m_TilesLocation = "textures/tiles/";
std::string LevelFactory::m_LevelsFilePath = "../Data/Levels.json";

std::vector<std::shared_ptr<GameObject>> LevelFactory::MakeLevel(Scene& scene, const glm::vec2& levelCenterPos, int levelNumber, 
	LevelInfo* levelInfo)
{
	std::ifstream levelFile(m_LevelsFilePath);
	json levels;
	levelFile >> levels;

	json levelToMake = nullptr;
	
	for (auto& level : levels)
	{
		const int levelNum = level["LevelNumber"];
		if(levelNum == levelNumber)
		{
			levelToMake = level;
			break;
		}
	}

	std::vector<std::shared_ptr<GameObject>> tiles{};
	if (levelToMake != nullptr)
	{
		const int size = levelToMake["LevelSize"];
		std::vector<std::string> tileTextures = levelToMake["TileTextures"];
		const bool isTriangle = levelToMake["IsTriangle"];
		const bool isCyclical = levelToMake["IsCyclical"];

		if (levelInfo != nullptr)
		{
			levelInfo->size = size;
			levelInfo->isTwoState = (tileTextures.size() == 2) ? true : false;
		}
		
		const float horizontalStep = m_TileSize / 2;
		const float verticalStep = m_TileSize * 0.75f;
		const float halfPyramidSize = GetPyramidHeight(size) / 2;

		glm::vec2 tilePos = { levelCenterPos.x - m_TileSize/2, levelCenterPos.y - halfPyramidSize };

		for (int row = 0; row < size; row++)
		{
			int colsToMake = size;
			if (isTriangle)
				colsToMake -= row;

			const glm::vec2 rowStartPos = tilePos;

			for (int col = 0; col < colsToMake; col++)
			{
				std::shared_ptr<GameObject> tile = TileFactory::MakeTile(
					tileTextures,
					tilePos.x,
					tilePos.y,
					m_TileSize,
					row,
					col,
					isCyclical);

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
	}

	return tiles;
}

//void LevelFactory::LinkTiles(std::vector<std::shared_ptr<boop::GameObject>>& levelTiles)
//{
//	for (auto& tile : levelTiles)
//	{
//		LinkTile(tile->GetComponentOfType<TileComponent>(), levelTiles);
//	}
//}
//
//void LevelFactory::LinkTile(TileComponent* tile, const std::vector<std::shared_ptr<GameObject>>& levelTiles)
//{
//	int row = tile->GetRow();
//	int col = tile->GetColumn();
//
//}

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
