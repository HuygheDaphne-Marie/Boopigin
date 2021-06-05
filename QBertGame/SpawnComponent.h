#pragma once
#include <Component.h>
#include <memory>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)
class LevelComponent;

class SpawnComponent final : public boop::Component
{
public:
	explicit SpawnComponent(LevelComponent* level, float defaultSpawnTime = 5.f);


	
	void Update() override;

	float m_SlickSamSpawnTime;
	
private:
	LevelComponent* m_pLevel;
	
	std::weak_ptr<boop::GameObject> m_pSlick{};
	std::weak_ptr<boop::GameObject> m_pSam{};

	// Slick & Sam
	float m_SlickSpawnTimer = 0.f;
	float m_SamSpawnTimer = 0.f;
	std::vector<glm::ivec2> m_SlickSamSpawnPositions{{0,1}, {1,0}};


	static bool IsEntityAlive(const std::weak_ptr<boop::GameObject>& entity);
	static glm::ivec2 GetStartPos(const std::vector<glm::ivec2>& possibleStartPositions);
};

