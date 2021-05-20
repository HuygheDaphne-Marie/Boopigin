#include "GameSetup.h"
#include <memory>
#include <SceneManager.h>
#include <Scene.h>
#include <TransformComponent.h>
#include <TextureComponent.h>

using namespace boop;

void GameSetup::LoadGame() const
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Game");
	auto go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent(0, 0));
	go->AddComponent(new TextureComponent("background.jpg"));
	scene.Add(go);
}
