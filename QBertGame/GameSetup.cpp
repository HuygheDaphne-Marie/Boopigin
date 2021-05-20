#include "GameSetup.h"
#include <memory>
#include <SceneManager.h>
#include <Scene.h>
#include <TransformComponent.h>
#include <TextureComponent.h>

#include "TileFactory.h"

using namespace boop;

void GameSetup::LoadGame() const
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Game");

	scene.Add(TileFactory::MakeTile("unwalked_level1.png", "walked_level1.png", 0, 0));
	scene.Add(TileFactory::MakeTile("unwalked_level1.png", "walked_level1.png", -16, 24));
	scene.Add(TileFactory::MakeTile("unwalked_level1.png", "walked_level1.png", 16, 24));
}
