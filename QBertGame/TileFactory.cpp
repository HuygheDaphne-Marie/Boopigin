#include "TileFactory.h"
#include <TransformComponent.h>
#include <TextureComponent.h>
#include "TileComponent.h"

using namespace boop;

std::shared_ptr<GameObject> TileFactory::MakeTile(const std::vector<std::string>& textures, float posX, float posY, float size, int row, int col)
{
	auto go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent(posX, posY));
	go->AddComponent(new TextureComponent(textures[0], size, size));
	go->AddComponent(new TileComponent(textures, col, row));

	// Todo: might need to do more setup like link tiles together (pathfinding), though this might be done in a different function/class
	
	return go;
}
