#pragma once
#include <string>
#include <memory>
#include <GameObject.h>

static std::string TilesLocation = "textures/tiles/";

class TileFactory
{
public:
	// take walked on and not walked on texture & position and turn it into a tile/cube
	static std::shared_ptr<boop::GameObject> MakeTile(const std::string& unwalkedTexturePath, const std::string& walkedTexturePath, float posX, float posY);

private:
	
};

