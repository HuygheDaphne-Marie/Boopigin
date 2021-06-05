#include "SpawnComponent.h"
#include <Timer.h>
#include "LevelComponent.h"
#include "EnemyFactory.h"
#include <random>

SpawnComponent::SpawnComponent(LevelComponent* level, float defaultSpawnTime)
	: m_SlickSamSpawnTime(defaultSpawnTime)
	, m_pLevel(level)
{
}

void SpawnComponent::Update()
{
	if (!IsEntityAlive(m_pSam))
	{
		// count up for sam
		m_SamSpawnTimer += boop::Timer::GetInstance().GetElapsedSec();
		if (m_SamSpawnTimer >= m_SlickSamSpawnTime)
		{
			const auto sam = EnemyFactory::MakeSam(*m_pLevel->GetLevelScene(), m_pLevel, GetStartPos(m_SlickSamSpawnPositions));
			m_SamSpawnTimer = 0.f;
			m_pLevel->AddEntity(sam);
			m_pSam = sam;
		}
	}
	if (!IsEntityAlive(m_pSlick))
	{
		// count up for slick
		m_SlickSpawnTimer += boop::Timer::GetInstance().GetElapsedSec();
		if (m_SlickSpawnTimer >= m_SlickSamSpawnTime)
		{
			const auto slick = EnemyFactory::MakeSlick(*m_pLevel->GetLevelScene(), m_pLevel, GetStartPos(m_SlickSamSpawnPositions));
			m_SlickSpawnTimer = 0.f;
			m_pLevel->AddEntity(slick);
			m_pSlick = slick;
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
