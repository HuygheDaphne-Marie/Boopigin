#pragma once
#include <Component.h>
#include <memory>
#include "TileComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)
#include "Scene.h"
#include <EventQueue.h>

class LevelComponent final : public boop::Component, IEventListener
{
public:
	LevelComponent(const std::string& sceneName, const glm::vec2& levelCenterPos);

	bool IsCoordinateInBounds(const glm::ivec2& coordinate) const;
	TileComponent* GetTileWithCoordinate(const glm::ivec2& coordinate);

	void Update() override;

	bool OnEvent(const Event& event) override;

	void AddPlayer(std::shared_ptr<boop::GameObject> player);

private:
	//boop::Scene m_Scene;
	std::shared_ptr<boop::Scene> m_Scene;
	glm::vec2 m_WindowCenter;
	std::vector<TileComponent*> m_LevelTiles;
	int m_LevelSize;
	int m_LevelNumber;
	
	std::vector<std::weak_ptr<boop::GameObject>> m_Players;
	
	bool AreAllTilesFlipped() const;
	void LoadLevel(int levelNumber);
	void ClearLevel();
	void LoadNextLevel();
};

