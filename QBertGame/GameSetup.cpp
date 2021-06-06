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

#include "MenuSelectComponent.h"

using namespace boop;

GameSetup::GameSetup(int windowWidth, int windowHeight)
	: m_WindowWidth(windowWidth)
	, m_WindowHeight(windowHeight)
{	
}

void GameSetup::LoadGame() const
{
	// Game Scene
	std::string sceneName = "game";
	Scene& gameScene = SceneManager::GetInstance().CreateScene(sceneName);
	SceneManager::GetInstance().SetSceneAsActive(sceneName);

	auto go = std::make_shared<GameObject>();
	auto* levelComponent = new LevelComponent(sceneName, { m_WindowWidth, m_WindowHeight });
	go->AddComponent(levelComponent);
	auto* scoreData = new ScoreDataComponent();
	go->AddComponent(scoreData);
	go->AddComponent(new SpawnComponent(levelComponent));
	gameScene.Add(go);

	const auto scoreTracker = QBertFactory::MakeScoreTracker(gameScene, go);
	const auto scoreText = scoreTracker->GetComponentOfType<TextComponent>();
	scoreTracker->GetComponentOfType<TransformComponent>()->SetPosition(static_cast<float>(m_WindowWidth / 2 - scoreText->GetWidth() / 2), 0);

	levelComponent->SetGameMode(GameMode::versus);
	
	/*
			KeyInfo(ControllerButton::ButtonB),
			KeyInfo(ControllerButton::ButtonA),
			KeyInfo(ControllerButton::ButtonX),
			KeyInfo(ControllerButton::ButtonY)
	 */

	// Main Menu
	const auto font = boop::ResourceManager::GetInstance().LoadFont("lingua.otf", 32);
	
	sceneName = "menu";
	Scene& menuScene = SceneManager::GetInstance().CreateScene(sceneName);
	SceneManager::GetInstance().SetSceneAsActive(sceneName);

	go = std::make_shared<GameObject>();
	auto mainMenu = new MenuSelectComponent(levelComponent);
	go->AddComponent(mainMenu);
	menuScene.Add(go);

	go = std::make_shared<GameObject>();
	auto btnText = new TextComponent("Single Player", font);
	go->AddComponent(btnText);
	go->AddComponent(new TransformComponent(
		static_cast<float>(m_WindowWidth / 2)  - btnText->GetWidth()/2,
		m_WindowHeight / 4 - static_cast<float>(btnText->GetHeight())
	));
	mainMenu->AddButton(go);
	go->AddTag("single");
	menuScene.Add(go);

	go = std::make_shared<GameObject>();
	btnText = new TextComponent("Co op", font);
	go->AddComponent(btnText);
	go->AddComponent(new TransformComponent(
		static_cast<float>(m_WindowWidth / 2) - btnText->GetWidth() / 2,
		(m_WindowHeight / 4) * 2 - static_cast<float>(btnText->GetHeight())
	));
	mainMenu->AddButton(go);
	go->AddTag("coop");
	menuScene.Add(go);

	go = std::make_shared<GameObject>();
	btnText = new TextComponent("Versus", font);
	go->AddComponent(btnText);
	go->AddComponent(new TransformComponent(
		static_cast<float>(m_WindowWidth / 2) - btnText->GetWidth() / 2,
		(m_WindowHeight / 4) * 3 - static_cast<float>(btnText->GetHeight())
	));
	mainMenu->AddButton(go);
	go->AddTag("versus");
	menuScene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new TextComponent(">", font));
	go->AddComponent(new TransformComponent());
	mainMenu->AddSelector(go);
	menuScene.Add(go);

	//SceneManager::GetInstance().SetSceneAsActive("game");
}
