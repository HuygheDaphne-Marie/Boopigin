#pragma once
#include <Component.h>
#include <string>

// Contains logic for a tile
// Will change color of tile and hold connections to other tiles for path finding
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

private:
	std::string m_WalkedTexturePath;
	const int m_TilePosX; // col
	const int m_TilePosY; // row
};

