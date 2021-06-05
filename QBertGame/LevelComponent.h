#pragma once
#include <Component.h>
#include <memory>
#include "TileComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)
#include "Scene.h"
#include <IEventListener.h>
class MovementComponent;

class LevelComponent final : public boop::Component, IEventListener
{
public:
	LevelComponent(const std::string& sceneName, const glm::vec2& levelCenterPos);

	bool IsCoordinateInBounds(const glm::ivec2& coordinate) const;
	TileComponent* GetTileWithCoordinate(const glm::ivec2& coordinate);

	void Update() override;

	bool OnEvent(const Event& event) override;

	void AddEntity(std::shared_ptr<boop::GameObject> player);

	std::shared_ptr<boop::Scene> GetLevelScene() const;

private:
	std::shared_ptr<boop::Scene> m_Scene;
	glm::vec2 m_WindowCenter;
	std::vector<TileComponent*> m_LevelTiles;
	int m_LevelSize;
	int m_LevelNumber;
	
	std::vector<std::weak_ptr<boop::GameObject>> m_Entities;
	
	bool AreAllTilesFlipped() const;
	void LoadLevel(int levelNumber);
	void ClearLevel();
	void LoadNextLevel();

	std::shared_ptr<boop::GameObject> GetSharedFromRawPointer(boop::GameObject* gameObject);
	MovementComponent* GetMovementComponentFromEntity(std::weak_ptr<boop::GameObject> entity);
	void DoCollisionCheck(boop::GameObject* jumpedEntity);
};

