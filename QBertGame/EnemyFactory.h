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

	static std::shared_ptr<boop::GameObject> MakeCoilyEgg(
		boop::Scene& scene,
		LevelComponent* pLevel,
		const glm::ivec2& startCoordinate = { 0,0 });
	
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
	static float m_LeapCooldownTime;
	static unsigned int m_Depth;

	static int m_SlickSamScoreGain;
	static int m_SquareSrcSize;
	static int m_SquareEnemyDstSize;
	static std::string m_SlickTexturePath;
	static std::string m_SamTexturePath;

	static int m_CoilySrcWidth;
	static int m_CoilySrcHeight;
	static int m_CoilyDstWidth;
	static int m_CoilyDstHeight;
	static std::string m_CoilyEggTexturePath;
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

