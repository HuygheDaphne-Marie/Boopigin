#include "GameSetup.h"
#include <memory>
#include <SceneManager.h>
#include <Scene.h>

#include "TileFactory.h"

using namespace boop;

void GameSetup::LoadGame() const
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Game");

	const float tileSize = 128.f;
	const float heightOffset = tileSize * 0.75;
	
	scene.Add(TileFactory::MakeTile("unwalked_level1.png", "walked_level1.png", 0, 0, tileSize));
	scene.Add(TileFactory::MakeTile("unwalked_level1.png", "walked_level1.png", -tileSize/2, heightOffset, tileSize));
	scene.Add(TileFactory::MakeTile("unwalked_level1.png", "walked_level1.png", tileSize/2, heightOffset, tileSize));
}
