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
	const int levelSize = 3;
	std::vector<std::shared_ptr<GameObject>> levelTiles = LevelFactory::MakeLevel(scene, {300, 200}, 1, levelSize);

	auto go = std::make_shared<GameObject>();
	auto* levelComponent = new LevelComponent(levelTiles, levelSize);
	go->AddComponent(levelComponent);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	auto* state = new StateComponent();
	go->AddComponent(state);
	
	auto* transform = new TransformComponent();
	go->AddComponent(transform);
	auto* playerJumper = new JumpComponent(transform, state, 2.0f);
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
	go->AddComponent(new TextureComponent("textures/qbert.png"));
	scene.Add(go);
}
