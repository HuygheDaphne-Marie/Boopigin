#pragma once
#include <Component.h>
#include "TileComponent.h"
#include "LevelComponent.h"
#include "JumpComponent.h"

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
	MovementComponent(TileComponent* startTile, LevelComponent* level, JumpComponent* jumper);

	void Update() override;
	
	bool MoveUp();
	bool MoveRight();
	bool MoveDown();
	bool MoveLeft();
	virtual bool Move(Direction movementDirection);
	virtual bool MoveTo(const glm::ivec2& tileCoordinate, Direction direction);

private:
	friend class PlayerMovementComponent;
	TileComponent* m_pCurrentTile;
	LevelComponent* m_pLevel;
	JumpComponent* m_pJumper;
	bool m_HasStarted;

	glm::vec2 GetTileStandPosition(TileComponent* tile) const;
};

