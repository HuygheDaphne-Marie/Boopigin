#pragma once
#include <string>
#include <memory>
#include <GameObject.h>

//static std::string TilesLocation = "textures/tiles/";

class TileFactory
{
public:
	// take walked on and not walked on texture & position and turn it into a tile/cube
	// Todo: this is a lot of vars
	static std::shared_ptr<boop::GameObject> MakeTile(
		const std::vector<std::string>& textures,
		float posX, 
		float posY, 
		float size, 
		int row, 
		int col,
		bool isCyclical);


};

