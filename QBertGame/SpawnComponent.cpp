#include "SpawnComponent.h"
#include <Timer.h>
#include "LevelComponent.h"
#include "EnemyFactory.h"
#include <random>

#include "MovementComponent.h"

SpawnComponent::SpawnComponent(LevelComponent* level, float defaultSpawnTime)
	: m_SlickSamSpawnTime(defaultSpawnTime)
	, m_UggWrongwaySpawnTime(defaultSpawnTime)
	, m_CoilySpawnTime(defaultSpawnTime)
	, m_pLevel(level)
{
}

void SpawnComponent::Update()
{
	IncrementTimeIfDead(m_SamSpawnTimer, m_pSam);
	IncrementTimeIfDead(m_SlickSpawnTimer, m_pSlick);
	IncrementTimeIfDead(m_UggSpawnTimer, m_pUgg);
	IncrementTimeIfDead(m_WrongwaySpawnTimer, m_pWrongway);
	IncrementTimeIfDead(m_CoilySpawnTimer, m_pCoily);

	// Sucks that this is so manual, but can't be asked to figure out the function binding for this right now
	// Spawns //
	if (m_SamSpawnTimer >= m_SlickSamSpawnTime)
	{
		const auto sam = EnemyFactory::MakeSam(*m_pLevel->GetLevelScene(), m_pLevel, GetStartPos(m_SlickSamSpawnPositions));
		m_SamSpawnTimer = 0.f;
		m_pLevel->AddEntity(sam);
		m_pSam = sam;
	}
	if (m_SlickSpawnTimer >= m_SlickSamSpawnTime)
	{
		const auto slick = EnemyFactory::MakeSlick(*m_pLevel->GetLevelScene(), m_pLevel, GetStartPos(m_SlickSamSpawnPositions));
		m_SlickSpawnTimer = 0.f;
		m_pLevel->AddEntity(slick);
		m_pSlick = slick;
	}
	if (m_UggSpawnTimer >= m_UggWrongwaySpawnTime)
	{
		const auto ugg = EnemyFactory::MakeUgg(*m_pLevel->GetLevelScene(), m_pLevel, { 0, m_pLevel->GetLevelSize() - 1 });
		m_UggSpawnTimer = 0.f;
		m_pLevel->AddEntity(ugg);
		m_pUgg = ugg;
	}
	if (m_WrongwaySpawnTimer >= m_UggWrongwaySpawnTime)
	{
		const auto wrongway = EnemyFactory::MakeWrongway(*m_pLevel->GetLevelScene(), m_pLevel, { m_pLevel->GetLevelSize() - 1, 0 });
		m_WrongwaySpawnTimer = 0.f;
		m_pLevel->AddEntity(wrongway);
		m_pWrongway = wrongway;
	}
	if (m_CoilySpawnTimer >= m_CoilySpawnTime)
	{
		const auto coilyEgg = EnemyFactory::MakeCoilyEgg(*m_pLevel->GetLevelScene(), m_pLevel, { 0, 0 });
		m_CoilySpawnTimer = 0.f;
		m_pLevel->AddEntity(coilyEgg);
		m_pCoily = coilyEgg;
	}

	// Check if coily egg can hatch
	if (auto coily = m_pCoily.lock())
	{
		if (coily->HasTag("egg") )
		{
			// egg has reached the bottom so get it's pos and spawn coily there
			const glm::ivec2 eggPos = coily->GetComponentOfType<MovementComponent>()->GetCurrentPosition();
			if (IsPosAtBottomEdgeOfLevel(eggPos))
			{
				coily->MarkForDelete();
				
				const auto hatchedCoily = EnemyFactory::MakeCoily(*m_pLevel->GetLevelScene(), m_pLevel, eggPos);
				m_pLevel->AddEntity(hatchedCoily);
				m_pCoily = hatchedCoily;
			}
		}
	}
}

bool SpawnComponent::IsEntityAlive(const std::weak_ptr<boop::GameObject>& entity)
{
	return !entity.expired();
}
glm::ivec2 SpawnComponent::GetStartPos(const std::vector<glm::ivec2>& possibleStartPositions)
{
	const int randomIndex = rand() % possibleStartPositions.size();
	return possibleStartPositions[randomIndex];
}

void SpawnComponent::IncrementTimeIfDead(float& timePassedSinceDeath, std::weak_ptr<boop::GameObject>& entityReference)
{
	if (!IsEntityAlive(entityReference))
		timePassedSinceDeath += boop::Timer::GetInstance().GetElapsedSec();
}

bool SpawnComponent::IsPosAtBottomEdgeOfLevel(const glm::ivec2& pos) const
{
	return pos.x + pos.y == m_pLevel->GetLevelSize() - 1;
}
