#include "GameSetup.h"
#include <SceneManager.h>
#include "LevelFactory.h"

//#include "TileComponent.h"

using namespace boop;

void GameSetup::LoadGame() const
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Game");
	std::vector<std::shared_ptr<GameObject>> levelTiles = LevelFactory::MakeLevel(scene, {300, 200}, 1, 3);

	//for (auto& tile : levelTiles)
	//{
	//	tile->GetComponentOfType<TileComponent>()->OnWalked();
	//}
}
