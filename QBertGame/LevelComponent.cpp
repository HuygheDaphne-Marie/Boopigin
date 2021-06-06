#include "LevelComponent.h"
#include "LevelFactory.h"
#include <EventQueue.h>

#include "PlayerDataComponent.h"
#include "JumpComponent.h"
#include "ControlledMovementComponent.h"
#include "BehaviorMovementComponent.h"
#include "CollisionComponent.h"
#include "ScoreDataComponent.h"
#include "QBertFactory.h"
#include <TextComponent.h>
#include "SpawnComponent.h"

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

std::vector<boop::KeyInfo> LevelComponent::m_PlayerOneKeys =
{
		boop::KeyInfo(SDLK_KP_9),
		boop::KeyInfo(SDLK_KP_3),
		boop::KeyInfo(SDLK_KP_1),
		boop::KeyInfo(SDLK_KP_7)
};
std::vector<boop::KeyInfo> LevelComponent::m_PlayerTwoKeys =
{
		boop::KeyInfo(SDLK_e),
		boop::KeyInfo(SDLK_c),
		boop::KeyInfo(SDLK_z),
		boop::KeyInfo(SDLK_q)
};
/*
		std::vector<KeyInfo> playerTwoKeys = {
			KeyInfo(ControllerButton::ButtonB),
			KeyInfo(ControllerButton::ButtonA),
			KeyInfo(ControllerButton::ButtonX),
			KeyInfo(ControllerButton::ButtonY)
		};
 */

LevelComponent::LevelComponent(const std::string& sceneName, const glm::vec2& window)
	: m_Scene(boop::SceneManager::GetInstance().GetScene(sceneName))
	, m_WindowCenter({ window.x / 2, window.y / 2 })
	, m_WindowSizes(window)
	, m_LevelSize(0)
	, m_LevelNumber(1)
	, m_HasGameStarted(false)
	, m_GameMode(GameMode::single)
{
	LoadLevel(m_LevelNumber);
	EventQueue::GetInstance().Subscribe("PlayerDied", this);
	EventQueue::GetInstance().Subscribe("PlayerTakeDamage", this);
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

void LevelComponent::Startup()
{
	// Setup single, coop, versus here
	m_HasGameStarted = true;

	// Setup player1 (Always happens)
	std::vector<glm::ivec2> startPositions;
	switch (m_GameMode)
	{
	case GameMode::coop:
		startPositions.push_back({ 0, GetLevelSize() - 1 });
		startPositions.push_back({ GetLevelSize() - 1, 0 });
		break;
		default:
			startPositions.push_back({ 0, 0 });
			break;
	}

	const auto playerOne = QBertFactory::MakePlayer(*m_Scene, this, m_PlayerOneKeys, startPositions[0]);
	const auto lifeTracker = QBertFactory::MakePlayerTracker(*m_Scene, playerOne);
	AddEntity(playerOne);
	
	if (m_GameMode == GameMode::coop)
	{
		const auto playerTwo = QBertFactory::MakePlayer(*m_Scene, this, m_PlayerTwoKeys, startPositions[1]);
		const auto lifeTrackerTwo = QBertFactory::MakePlayerTracker(*m_Scene, playerTwo);

		const auto trackTwoText = lifeTrackerTwo->GetComponentOfType<boop::TextComponent>();
		lifeTrackerTwo->GetComponentOfType<boop::TransformComponent>()->SetPosition(m_WindowSizes.x - trackTwoText->GetWidth(), 0);
		
		AddEntity(playerTwo);
	}
	
	if (m_GameMode == GameMode::versus)
	{
		m_pOwner->GetComponentOfType<SpawnComponent>()->SetupVersus(m_PlayerTwoKeys);
	}
}

void LevelComponent::Update()
{
	if (AreAllTilesFlipped())
	{
		LoadNextLevel();
	}
	
	/* // having trouble deleting this damn reference and cleaning up the list
	for (int index = 0; index < m_Entities.size(); index++)
	{
		if (m_Entities[index].expired())
		{
			m_Entities[index] = m_Entities[m_Entities.size() - 1];
			index--;
		}
	}
	*/
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
	if (event.message == "PlayerTakeDamage")
	{
		ResetEnemyEntities();
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
	std::shared_ptr<boop::GameObject> closestQbert = nullptr;
	
	for (auto& entity : m_Entities)
	{
		if (auto lockedEntity = entity.lock())
		{
			if (lockedEntity->HasTag("qbert"))
			{
				if (closestQbert == nullptr)
				{
					closestQbert = lockedEntity;
					continue;
				}

				glm::ivec2 lockedPos = lockedEntity->GetComponentOfType<MovementComponent>()->GetCurrentPosition();
				glm::ivec2 myDeltaPos = lockedPos - pos;
				glm::ivec2 currentClosestDeltaPos = lockedEntity->GetComponentOfType<MovementComponent>()->GetCurrentPosition() - pos;

				if (myDeltaPos.length() < currentClosestDeltaPos.length())
				{
					closestQbert = lockedEntity;
				}
			}
		}
	}
	return closestQbert;
}

int LevelComponent::GetLevelSize() const
{
	return m_LevelSize;
}

void LevelComponent::SetGameMode(GameMode mode)
{
	if (!m_HasGameStarted)
	{
		m_GameMode = mode;
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

void LevelComponent::ResetEnemyEntities()
{
	for (auto& weak : m_Entities)
	{
		if (auto locked = weak.lock())
		{
			if (!locked->HasTag("qbert"))
			{
				locked->MarkForDelete();
			}
		}
	}
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
	auto currentScene = boop::SceneManager::GetInstance().GetActiveScene();
	auto myScene = m_Scene;
	
	const std::shared_ptr<boop::GameObject> ptrJumped = GetSharedFromRawPointer(jumpedEntity);
	if (ptrJumped == nullptr)
		return;
	
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
