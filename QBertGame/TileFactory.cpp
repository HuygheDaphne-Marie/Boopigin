#include "TileFactory.h"
#include <TransformComponent.h>
#include <TextureComponent.h>
#include "TileComponent.h"

using namespace boop;

std::shared_ptr<GameObject> TileFactory::MakeTile(const std::string& unwalkedTexturePath, const std::string& walkedTexturePath, float posX, float posY, float size, int row, int col)
{
	auto go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent(posX, posY));
	go->AddComponent(new TextureComponent(TilesLocation + unwalkedTexturePath, size, size));
	go->AddComponent(new TileComponent(TilesLocation + walkedTexturePath, col, row));

	// Todo: might need to do more setup like link tiles together (pathfinding), though this might be done in a different function/class
	
	return go;
}
