#pragma once
#include <Component.h>
#include <memory>
#include "TileComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)
#include "Scene.h"
#include <Key.h>
#include <IEventListener.h>
class MovementComponent;

enum class GameMode
{
	single,
	coop,
	versus
};

class LevelComponent final : public boop::Component, IEventListener
{
public:
	LevelComponent(const std::string& sceneName, const glm::vec2& window);

	bool IsCoordinateInBounds(const glm::ivec2& coordinate) const;
	TileComponent* GetTileWithCoordinate(const glm::ivec2& coordinate);

	void Startup() override;
	void Update() override;

	bool OnEvent(const Event& event) override;

	void AddEntity(std::shared_ptr<boop::GameObject> player);

	std::shared_ptr<boop::Scene> GetLevelScene() const;
	std::shared_ptr<boop::GameObject> GetQbertClosestTo(const glm::ivec2& pos);
	int GetLevelSize() const;

	void SetGameMode(GameMode mode);

private:
	std::shared_ptr<boop::Scene> m_Scene;
	glm::vec2 m_WindowCenter;
	glm::vec2 m_WindowSizes;
	std::vector<TileComponent*> m_LevelTiles{};
	int m_LevelSize;
	int m_LevelNumber;
	
	bool m_HasGameStarted;
	GameMode m_GameMode;
	
	std::vector<std::weak_ptr<boop::GameObject>> m_Entities{};
	
	bool AreAllTilesFlipped() const;
	void LoadLevel(int levelNumber);
	void ClearLevel();
	void LoadNextLevel();

	void ResetEnemyEntities();

	std::shared_ptr<boop::GameObject> GetSharedFromRawPointer(boop::GameObject* gameObject);
	void DoCollisionCheck(boop::GameObject* jumpedEntity);

	static std::vector<boop::KeyInfo> m_PlayerOneKeys;
	static std::vector<boop::KeyInfo> m_PlayerTwoKeys;
};

