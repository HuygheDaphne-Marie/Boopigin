#include "GameSetup.h"
#include <SceneManager.h>
#include "LevelFactory.h"

#include <TextureComponent.h>
#include "LevelComponent.h"
#include "PlayerMovementComponent.h"
#include "JumpComponent.h"
#include "StateComponent.h"

using namespace boop;

void GameSetup::LoadGame() const
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Game");
	const glm::vec2 screenCenter = { 300, 200 };
	LevelInfo levelInfo{};
	std::vector<std::shared_ptr<GameObject>> levelTiles = LevelFactory::MakeLevel(scene, screenCenter, 1, &levelInfo);

	auto go = std::make_shared<GameObject>();
	auto* levelComponent = new LevelComponent(levelTiles, levelInfo.size);
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
	go->AddComponent(new PlayerMovementComponent(levelTiles[0]->GetComponentOfType<TileComponent>(), levelComponent, playerJumper, keys));
	scene.Add(go);
}
