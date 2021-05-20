#include "GameSetup.h"
#include <SceneManager.h>
#include "LevelFactory.h"

using namespace boop;

void GameSetup::LoadGame() const
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Game");
	LevelFactory::MakeLevel(scene, 1, 3);
}
