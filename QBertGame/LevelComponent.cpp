#include "LevelComponent.h"
#include "LevelFactory.h"
#include <EventQueue.h>

#include "PlayerDataComponent.h"
#include "JumpComponent.h"
#include "ControlledMovementComponent.h"
#include "BehaviorMovementComponent.h"
#include "CollisionComponent.h"
#include "ScoreDataComponent.h"

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
	EventQueue::GetInstance().Subscribe("PlayerDied", this);
	EventQueue::GetInstance().Subscribe("JumpCompleted", this);
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

	//const auto removeItr = std::remove_if(m_Entities.begin(), m_Entities.end(),
	//	[](std::weak_ptr<boop::GameObject>& entity)
	//	{
	//		return entity.expired();
	//	}
	//);
	//m_Entities.erase(removeItr);
}

bool LevelComponent::OnEvent(const Event& event)
{
	if (event.message == "PlayerDied")
	{
		for (auto& weakEntity : m_Entities)
		{
			if (auto lockedEntity = weakEntity.lock())
			{
				if (lockedEntity->HasTag("qbert"))
				{
					lockedEntity->GetComponentOfType<PlayerDataComponent>()->Reset();
				}
			}
			// Todo: reset more stuff, like score, position
			auto scoreData = m_pOwner->GetComponentOfType<ScoreDataComponent>();
			scoreData->Reset();
		}
		m_LevelNumber = 0;
		LoadNextLevel();
		return true;
	}
	// Todo: reset entities, put players back in startPos & delete all other entities when player takes damage
	if (event.message == "JumpCompleted")
	{
		JumpComponent* jumper = event.GetData<JumpComponent*>();
		DoCollisionCheck(jumper->GetOwner());
	}
	return false;
}

void LevelComponent::AddEntity(std::shared_ptr<boop::GameObject> player)
{
	bool isAlreadyInList = false;
	for (auto& weakPtr : m_Entities)
	{
		if (weakPtr.lock() == player)
			isAlreadyInList = true;
	}
	if (!isAlreadyInList)
	{
		m_Entities.push_back(player);
	}
}

std::shared_ptr<boop::Scene> LevelComponent::GetLevelScene() const
{
	return m_Scene;
}

std::shared_ptr<boop::GameObject> LevelComponent::GetQbertClosestTo(const glm::ivec2& pos)
{
	int x = pos.x; // Todo: make this actually get the closest qbert
	x++;
	for (auto& entity : m_Entities)
	{
		if (auto lockedEntity = entity.lock())
		{
			if (lockedEntity->HasTag("qbert"))
			{
				return lockedEntity;
			}
		}
	}
	return nullptr;
}

int LevelComponent::GetLevelSize() const
{
	return m_LevelSize;
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

std::shared_ptr<boop::GameObject> LevelComponent::GetSharedFromRawPointer(boop::GameObject* gameObject)
{
	for (auto& entity : m_Entities)
	{
		if (auto lockedEntity = entity.lock())
		{
			if (lockedEntity.get() == gameObject)
			{
				return lockedEntity;
			}
		}
	}
	return nullptr;
}

void LevelComponent::DoCollisionCheck(boop::GameObject* jumpedEntity)
{
	const std::shared_ptr<boop::GameObject> ptrJumped = GetSharedFromRawPointer(jumpedEntity);
	MovementComponent* jumpedMovementComp = ptrJumped->GetComponentOfType<MovementComponent>();

	if (jumpedMovementComp == nullptr)
		return;

	for (auto& entity : m_Entities)
	{
		// Skip self
		if (entity.lock() == ptrJumped)
			continue;
		
		if (auto lockedEntity = entity.lock())
		{
			MovementComponent* otherMovementComp = lockedEntity->GetComponentOfType<MovementComponent>();
			// Skip things that don't have a movement component
			if (otherMovementComp == nullptr)
				continue;

			if (jumpedMovementComp->GetCurrentPosition() == otherMovementComp->GetCurrentPosition())
			{
				 // If the entity has a collision component, we tell it who it collided with
				if (auto collisionComp = ptrJumped->GetComponentOfType<CollisionComponent>())
				{
					collisionComp->OnCollision(lockedEntity);
				}
				if (auto collisionComp = lockedEntity->GetComponentOfType<CollisionComponent>())
				{
					collisionComp->OnCollision(ptrJumped);
				}
			}
		}
	}
}
