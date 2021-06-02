#pragma once
#include <Component.h>
#include <string>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

// Contains logic for a tile
// Will change color of tile and hold connections to other tiles for path finding
//enum class Direction
//{
//	top = 0,
//	right = 1,
//	bottom = 2,
//	left = 3
//};

class TileComponent final : public boop::Component
{
public:
	explicit TileComponent(const std::string& walkedTexturePath, int posX, int posY);
	~TileComponent() override = default;
	TileComponent(const TileComponent & other) = delete;
	TileComponent(TileComponent && other) = delete;
	TileComponent& operator=(const TileComponent & other) = delete;
	TileComponent& operator=(TileComponent && other) = delete;

	void OnWalked() const;

	int GetRow() const;
	int GetColumn() const;

private:
	std::string m_WalkedTexturePath;
	const int m_TileCol;
	const int m_TileRow;
	
	std::vector<TileComponent*> m_pAdjacentTiles = std::vector<TileComponent*>{};
};

