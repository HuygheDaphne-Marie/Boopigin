#pragma once
#include <Component.h>
#include <TransformComponent.h>
#include "TileComponent.h"
#include "LevelComponent.h"

// Knows which tile it is on, when moving in a direction checks which tile is there and jumps to it's location in an arc
enum class Direction
{
	up = 0,
	right = 1,
	down = 2,
	left = 3
};

class MovementComponent : public boop::Component
{
public:
	MovementComponent(TileComponent* startTile, LevelComponent* level, boop::TransformComponent* myTransform);

	bool MoveUp();
	bool MoveRight();
	bool MoveDown();
	bool MoveLeft();
	virtual bool Move(Direction movementDirection);

private:
	friend class PlayerMovementComponent;
	TileComponent* m_pCurrentTile;
	LevelComponent* m_pLevel;
	boop::TransformComponent* m_pTransform;

	static glm::vec2 GetTileStandPosition(TileComponent* tile);
};

