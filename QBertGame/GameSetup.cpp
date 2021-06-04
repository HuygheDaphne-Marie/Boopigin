#include "GameSetup.h"
#include <SceneManager.h>
#include "LevelFactory.h"

#include <TextureComponent.h>
#include "LevelComponent.h"
#include "PlayerMovementComponent.h"
#include "JumpComponent.h"
#include "StateComponent.h"

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
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new TextureComponent("textures/qbert.png", 32.f, 32.f));
	auto* transform = new TransformComponent();
	go->AddComponent(transform);
	
	auto* state = new StateComponent();
	go->AddComponent(state);
	auto* playerJumper = new JumpComponent(transform, state, 0.7f);
	go->AddComponent(playerJumper);
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
	go->AddComponent(new PlayerMovementComponent(levelComponent->GetTileWithCoordinate({0,0}), levelComponent, playerJumper, keys));
	scene.Add(go, 1);
}
