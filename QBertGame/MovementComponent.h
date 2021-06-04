#pragma once
#include <Component.h>
#include "TileComponent.h"
#include "LevelComponent.h"
#include "JumpComponent.h"
#include <TextureComponent.h>
#include <EventQueue.h>

enum class Direction
{
	up = 0,
	right = 1,
	down = 2,
	left = 3
};

//struct WalkData
//{
//	glm::ivec2 tileCoordinate;
//	bool isPlayer;
//};

class MovementComponent : public boop::Component, public IEventListener
{
public:
	MovementComponent(const glm::ivec2& startPos, LevelComponent* level, JumpComponent* jumper);

	void Update() override;
	
	bool MoveUp();
	bool MoveRight();
	bool MoveDown();
	bool MoveLeft();
	virtual bool Move(Direction movementDirection);
	virtual bool MoveTo(const glm::ivec2& tileCoordinate, Direction direction);

	bool OnEvent(const Event& event) override;

	bool ChangesTileStateOnWalk() const;

	void SetPosition(const glm::ivec2& coordinate);

	bool m_DoUnFlip;
	bool m_DoFlip;
	bool m_DoGainScore;

private:
	friend class PlayerMovementComponent;
	glm::ivec2 m_CurrentPos;
	LevelComponent* m_pLevel;
	JumpComponent* m_pJumper;
	bool m_HasStarted;
	
	glm::vec2 GetTileStandPosition(TileComponent* tile) const;
	static glm::vec2 GetTileStandPosition(TileComponent* tile, boop::TextureComponent* pQbertTexture);
};

