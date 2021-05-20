#include "LevelFactory.h"
#include <string>
#include <Scene.h>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

#include "TileFactory.h"

using namespace boop;

void LevelFactory::MakeLevel(boop::Scene& scene, int levelNumber, int size, bool isTriangle)
{
	const std::string walkedTexturePath = "walked_level" + std::to_string(levelNumber) + ".png";
	const std::string unwalkedTexturePath = "un" + walkedTexturePath;
	const float tileSize = 64.f; //todo: should be var? feels like a static const
	const float horizontalStep = tileSize / 2;
	const float verticalStep = tileSize * 0.75f;

	glm::vec2 tilePos = { 200,100 }; //todo: should be a var
	
	for (int row = 0; row < size; row++)
	{
		int colsToMake = size;
		if (isTriangle)
			colsToMake -= row;

		const glm::vec2 rowStartPos = tilePos;
		
		for (int col = 0; col < colsToMake; col++)
		{
			scene.Add(TileFactory::MakeTile(unwalkedTexturePath, walkedTexturePath, tilePos.x, tilePos.y, tileSize));

			// increment pos to down right
			tilePos.x += horizontalStep;
			tilePos.y += verticalStep;
		}

		// increment row and shift tiles to bottom left
		tilePos.x = rowStartPos.x - horizontalStep;
		tilePos.y = rowStartPos.y + verticalStep;
	}
}
