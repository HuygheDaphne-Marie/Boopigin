#include "LevelComponent.h"
#include "LevelFactory.h"
#include <EventQueue.h>

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

LevelComponent::LevelComponent(const std::string& sceneName, const glm::vec2& levelCenterPos)
	: m_Scene(boop::SceneManager::GetInstance().GetScene(sceneName))
	, m_WindowCenter(levelCenterPos)
	, m_LevelSize(0)
	, m_LevelNumber(1)
{
	LoadLevel(m_LevelNumber);
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

	return m_LevelTiles[index];
}

void LevelComponent::Update()
{
	if (AreAllTilesFlipped())
	{
		// if all tiles are flipped
		// load next level
		LoadNextLevel();
	}
	
}

bool LevelComponent::AreAllTilesFlipped() const
{
	if (m_LevelTiles.empty())
		return false;
	
	bool allTilesFlipped = true;
	for (auto* levelTile : m_LevelTiles)
	{
		if (levelTile->GetFlipState() != FlipState::flipped)
		{
			allTilesFlipped = false;
			break;
		}
	}
	return allTilesFlipped;
}

void LevelComponent::LoadLevel(int levelNumber)
{
	LevelInfo levelInfo{};
	std::vector<std::shared_ptr<boop::GameObject>> levelTiles = LevelFactory::MakeLevel(*m_Scene, m_WindowCenter, levelNumber, &levelInfo);
	m_LevelSize = levelInfo.size;
	
	for (auto& gameObject : levelTiles)
	{
		m_LevelTiles.push_back(gameObject->GetComponentOfType<TileComponent>());
	}
}

void LevelComponent::ClearLevel()
{
	for (auto& levelTile : m_LevelTiles)
	{
		m_Scene->Remove(levelTile->GetOwner());
	}
	m_LevelTiles.clear();
}

void LevelComponent::LoadNextLevel()
{
	ClearLevel();
	// Todo: Reset what needs to be reset (like player and stuff)
	m_LevelNumber++;
	LoadLevel(m_LevelNumber);
	EventQueue::GetInstance().Broadcast(new Event("NewLevelLoaded"));
}
