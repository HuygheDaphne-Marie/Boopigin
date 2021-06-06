#pragma once
#include <AnimationComponent.h>
#include "StateComponent.h"
#include "MovementComponent.h"

class BiDirectionalJumpAnimationComponent : public boop::AnimationComponent
{
public:
	BiDirectionalJumpAnimationComponent(const std::string& texturePath, int frameWidth, int frameHeight, int displayWidth = 0, int displayHeight = 0);

	void Startup() override;
	void Update() override;

private:
	StateComponent* m_pState;
	MovementComponent* m_pMovement;

	static int GetFrameFromDirection(Direction direction);
};

