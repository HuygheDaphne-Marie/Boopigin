#pragma once
#include <memory>
#include <string>
#include <GameObject.h>

#include "LevelComponent.h"

class EnemyFactory
{
public:
	static std::shared_ptr<boop::GameObject> MakeSlick(
		boop::Scene& scene,
		LevelComponent* pLevel,
		const glm::ivec2& startCoordinate = {0,0});

	static std::shared_ptr<boop::GameObject> MakeSam(
		boop::Scene& scene,
		LevelComponent* pLevel,
		const glm::ivec2& startCoordinate = {0,0});

	static std::shared_ptr<boop::GameObject> MakeCoily(
		boop::Scene& scene,
		LevelComponent* pLevel,
		const glm::ivec2& startCoordinate = { 0,0 });

	static std::shared_ptr<boop::GameObject> MakeUgg(
		boop::Scene& scene,
		LevelComponent* pLevel,
		const glm::ivec2& startCoordinate = { 0,0 });

	static std::shared_ptr<boop::GameObject> MakeWrongway(
		boop::Scene& scene,
		LevelComponent* pLevel,
		const glm::ivec2& startCoordinate = { 0,0 });

	static float m_LeapTime;
	static unsigned int m_Depth;

	static int m_SlickSamScoreGain;
	static float m_SquareEnemySize;
	static std::string m_SlickTexturePath;
	static std::string m_SamTexturePath;

	static float m_CoilyWidth;
	static float m_CoilyHeight;
	static std::string m_CoilyTexturePath;

	static std::string m_UggTexturePath;
	static std::string m_WrongwayTexturePath;

private:
	static std::shared_ptr<boop::GameObject> MakeTumbler(
		boop::Scene& scene,
		LevelComponent* pLevel,
		const std::string& texturePath,
		const glm::ivec2& startCoordinate = { 0,0 });

	static std::shared_ptr<boop::GameObject> MakeEscheresqueTumbler(
		boop::Scene& scene,
		LevelComponent* pLevel,
		const std::string& texturePath,
		bool standOnLeftSideOfTile,
		const glm::ivec2& startCoordinate = { 0,0 });
};

