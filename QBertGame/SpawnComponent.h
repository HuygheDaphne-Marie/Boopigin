#pragma once
#include <Component.h>
#include <memory>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

#include <functional>
class LevelComponent;

class SpawnComponent final : public boop::Component
{
public:
	explicit SpawnComponent(LevelComponent* level, float defaultSpawnTime = 10.f);

	void Update() override;

	float m_SlickSamSpawnTime;
	float m_UggWrongwaySpawnTime;
	float m_CoilySpawnTime;
	
private:
	LevelComponent* m_pLevel;
	
	std::weak_ptr<boop::GameObject> m_pSlick{};
	std::weak_ptr<boop::GameObject> m_pSam{};
	std::weak_ptr<boop::GameObject> m_pUgg{};
	std::weak_ptr<boop::GameObject> m_pWrongway{};
	std::weak_ptr<boop::GameObject> m_pCoily{};

	// Slick & Sam
	float m_SlickSpawnTimer = 0.f;
	float m_SamSpawnTimer = 0.f;
	float m_UggSpawnTimer = 0.f;
	float m_WrongwaySpawnTimer = 0.f;
	float m_CoilySpawnTimer = 0.f;
	
	std::vector<glm::ivec2> m_SlickSamSpawnPositions{{0,1}, {1,0}};

	static bool IsEntityAlive(const std::weak_ptr<boop::GameObject>& entity);
	static glm::ivec2 GetStartPos(const std::vector<glm::ivec2>& possibleStartPositions);

	static void IncrementTimeIfDead(float& timePassedSinceDeath, std::weak_ptr<boop::GameObject>& entityReference);

	bool IsPosAtBottomEdgeOfLevel(const glm::ivec2& pos) const;
	
	/* // such hopeful dreams
	void SpawnIfDeadForTime(const float timeItTakesToSpawn, float& timePassedSinceDeath, std::weak_ptr<boop::GameObject>& entityReference, 
		const std::vector<glm::ivec2>& possibleSpawns, std::function<std::shared_ptr<boop::GameObject>> functionToCallWhenSpawning);
	*/
};

