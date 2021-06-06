#include "GameSetup.h"
#include <SceneManager.h>
#include "LevelFactory.h"
#include "QBertFactory.h"
#include "EnemyFactory.h"

#include <TextureComponent.h>
#include <ResourceManager.h>
#include "LevelComponent.h"
#include "ControlledMovementComponent.h"

#include "ScoreDataComponent.h"
#include "SpawnComponent.h"

using namespace boop;

GameSetup::GameSetup(int windowWidth, int windowHeight)
	: m_WindowWidth(windowWidth)
	, m_WindowHeight(windowHeight)
{	
}

void GameSetup::LoadGame() const
{
	const std::string sceneName = "Game";
	Scene& scene = SceneManager::GetInstance().CreateScene(sceneName);
	const glm::vec2 screenCenter = { m_WindowWidth / 2, m_WindowHeight / 2 };

	auto go = std::make_shared<GameObject>();
	auto* levelComponent = new LevelComponent(sceneName, screenCenter);
	go->AddComponent(levelComponent);
	auto* scoreData = new ScoreDataComponent();
	go->AddComponent(scoreData);
	go->AddComponent(new SpawnComponent(levelComponent));
	scene.Add(go);

	std::vector<KeyInfo> keys = {
		KeyInfo(SDLK_KP_9),
		KeyInfo(SDLK_KP_3),
		KeyInfo(SDLK_KP_1),
		KeyInfo(SDLK_KP_7)
	};
	//std::vector<KeyInfo> keys = {
	//	KeyInfo(ControllerButton::ButtonB),
	//	KeyInfo(ControllerButton::ButtonA),
	//	KeyInfo(ControllerButton::ButtonX),
	//	KeyInfo(ControllerButton::ButtonY)
	//};
	auto player = QBertFactory::MakePlayer(scene, levelComponent, keys, { 0,0 });
	auto lifeTracker = QBertFactory::MakePlayerTracker(scene, player);
	auto scoreTracker = QBertFactory::MakeScoreTracker(scene, go);

	levelComponent->AddEntity(player);
}
