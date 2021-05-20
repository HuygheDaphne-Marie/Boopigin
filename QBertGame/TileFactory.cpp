#include "TileFactory.h"
#include <TransformComponent.h>
#include <TextureComponent.h>
#include "TileComponent.h"

using namespace boop;

std::shared_ptr<GameObject> TileFactory::MakeTile(const std::string& unwalkedTexturePath, const std::string& walkedTexturePath, float posX, float posY, float size)
{
	int thingy = static_cast<int>(size);
	thingy--;
	auto go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent(posX, posY));
	TextureComponent* pTextureComponent = new TextureComponent(TilesLocation + unwalkedTexturePath, size, size);
	//TextureComponent* pTextureComponent = new TextureComponent(TilesLocation + unwalkedTexturePath);
	go->AddComponent(pTextureComponent);
	go->AddComponent(new TileComponent(TilesLocation + walkedTexturePath));

	return go;
}
