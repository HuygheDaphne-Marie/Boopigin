#pragma once
#include <GameObject.h>
#include <Scene.h>
#include <string>
#include <Key.h>
#include "LevelComponent.h"

class QBertFactory
{
public:
	static std::shared_ptr<boop::GameObject> MakePlayer(
		boop::Scene& scene, 
		LevelComponent* pLevel, 
		std::vector<boop::KeyInfo>& controls,
		const glm::ivec2& startCoordinate);

	static std::shared_ptr<boop::GameObject> MakePlayerTracker(
		boop::Scene& scene,
		std::shared_ptr<boop::GameObject> playerToTrack);

	static std::shared_ptr<boop::GameObject> MakeScoreTracker(
		boop::Scene& scene,
		std::shared_ptr<boop::GameObject> scoreDataObject);

	static float m_QbertSize;
	static float m_QbertLeapTime;
	static std::string m_QBertTexturePath;
	static unsigned int m_QBertDepth;
	
	static std::string m_QBertTrackerFontPath;
	static unsigned int m_QBertTrackerFontSize;
	static unsigned int m_QBertTrackerDepth;
};

