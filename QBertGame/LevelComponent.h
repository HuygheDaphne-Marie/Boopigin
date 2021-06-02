#pragma once
#include <Component.h>
#include <memory>
#include "TileComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

class LevelComponent : public boop::Component
{
public:
	LevelComponent(std::vector<std::shared_ptr<boop::GameObject>> levelTiles, int levelSize);

	bool IsCoordinateInBounds(const glm::ivec2& coordinate) const;
	TileComponent* GetTileWithCoordinate(const glm::ivec2& coordinate);

private:
	std::vector<std::shared_ptr<boop::GameObject>> m_LevelTiles;
	int m_LevelSize;
};

