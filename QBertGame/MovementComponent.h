#pragma once
#include <Component.h>
#include "TileComponent.h"
#include "LevelComponent.h"
#include "JumpComponent.h"
#include <TextureComponent.h>
#include <IEventListener.h>

enum class Direction
{
	up = 0,
	right = 1,
	down = 2,
	left = 3,
	escheresqueRight,
	escheresqueLeft
};

class MovementComponent : public boop::Component, public IEventListener
{
public:
	MovementComponent(const glm::ivec2& startPos, LevelComponent* level, JumpComponent* jumper);

	void Startup() override;
	
	bool MoveUp();
	bool MoveRight();
	bool MoveDown();
	bool MoveLeft();
	bool MoveEscheresqueRight();
	bool MoveEscheresqueLeft();
	virtual bool Move(Direction movementDirection);
	virtual bool MoveTo(const glm::ivec2& tileCoordinate, Direction direction);

	bool OnEvent(const Event& event) override;

	bool ChangesTileStateOnWalk() const;

	void SetPosition(const glm::ivec2& coordinate);

	glm::ivec2 GetCurrentPosition() const;
	const LevelComponent* GetLevel() const;
	const JumpComponent* GetJumper() const;

	bool m_DoUnFlip;
	bool m_DoFlip;
	bool m_DoGainScore;

protected:
	glm::ivec2 m_CurrentPos;
	LevelComponent* m_pLevel;
	JumpComponent* m_pJumper;
	
	glm::vec2 GetTileStandPosition(TileComponent* tile) const;
	static glm::vec2 GetTileStandPosition(TileComponent* tile, boop::TextureComponent* pQbertTexture);
};

