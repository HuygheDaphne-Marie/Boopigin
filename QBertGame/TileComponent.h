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

enum class FlipKind
{
	twoState,
	threeState
};
enum class FlipState
{
	unFlipped = 0,
	intermediate = 1,
	flipped = 2
};

class TileComponent final : public boop::Component
{
public:
	explicit TileComponent(std::vector<std::string> textures, int posX, int posY, bool isCyclical);
	~TileComponent() override = default;
	TileComponent(const TileComponent & other) = delete;
	TileComponent(TileComponent && other) = delete;
	TileComponent& operator=(const TileComponent & other) = delete;
	TileComponent& operator=(TileComponent && other) = delete;

	//void OnWalked(bool isFlipping = true, bool isPlayer = true);
	void OnFlip(bool gainScore);
	void OnUnFlip(bool gainScore);
	void UpdateTexture();

	int GetRow() const;
	int GetColumn() const;

	FlipState GetFlipState() const;

private:
	std::vector<std::string> m_TileTextures;
	const int m_TileCol;
	const int m_TileRow;
	FlipKind m_FlipKind;
	FlipState m_FlipState;
	bool m_IsCyclical;
	
	std::vector<TileComponent*> m_pAdjacentTiles = std::vector<TileComponent*>{};

	bool HasNextFlipState() const;
	bool HasPreviousFlipState() const;
	void ToNextFlipState();
	void ToPreviousFlipState();
};

