#pragma once
#include <Component.h>
#include <memory>
#include "TileComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)
#include "Scene.h"

class LevelComponent final : public boop::Component
{
public:
	LevelComponent(const std::string& sceneName, const glm::vec2& levelCenterPos);

	bool IsCoordinateInBounds(const glm::ivec2& coordinate) const;
	TileComponent* GetTileWithCoordinate(const glm::ivec2& coordinate);

	void Update() override;

private:
	//boop::Scene m_Scene;
	std::shared_ptr<boop::Scene> m_Scene;
	glm::vec2 m_WindowCenter;
	
	std::vector<TileComponent*> m_LevelTiles;
	int m_LevelSize;
	int m_LevelNumber;
	
	// ptr to playerdata (HP and such)
	
	bool AreAllTilesFlipped() const;
	void LoadLevel(int levelNumber);
	void ClearLevel();
	void LoadNextLevel();
};

