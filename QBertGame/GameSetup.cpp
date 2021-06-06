#include "GameSetup.h"
#include <SceneManager.h>
#include "LevelFactory.h"
#include "QBertFactory.h"
#include "EnemyFactory.h"

#include <TextureComponent.h>
#include <TextComponent.h>
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
	// Game Scene
	{
		/*
		std::vector<KeyInfo> playerOneKeys = {
			KeyInfo(SDLK_KP_9),
			KeyInfo(SDLK_KP_3),
			KeyInfo(SDLK_KP_1),
			KeyInfo(SDLK_KP_7)
		};
		std::vector<KeyInfo> playerTwoKeys = {
			KeyInfo(SDLK_e),
			KeyInfo(SDLK_c),
			KeyInfo(SDLK_z),
			KeyInfo(SDLK_q)
		};
		*/
		
		const std::string sceneName = "game";
		Scene& scene = SceneManager::GetInstance().CreateScene(sceneName);
		SceneManager::GetInstance().SetSceneAsActive(sceneName);

		auto go = std::make_shared<GameObject>();
		auto* levelComponent = new LevelComponent(sceneName, {m_WindowWidth, m_WindowHeight});
		go->AddComponent(levelComponent);
		auto* scoreData = new ScoreDataComponent();
		go->AddComponent(scoreData);
		go->AddComponent(new SpawnComponent(levelComponent));
		scene.Add(go);

		const auto scoreTracker = QBertFactory::MakeScoreTracker(scene, go);
		const auto scoreText = scoreTracker->GetComponentOfType<TextComponent>();
		scoreTracker->GetComponentOfType<TransformComponent>()->SetPosition(static_cast<float>(m_WindowWidth / 2 - scoreText->GetWidth() / 2), 0);

		levelComponent->SetGameMode(GameMode::versus);
	}
	/*
			KeyInfo(ControllerButton::ButtonB),
			KeyInfo(ControllerButton::ButtonA),
			KeyInfo(ControllerButton::ButtonX),
			KeyInfo(ControllerButton::ButtonY)
	 */
}
