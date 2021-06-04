#pragma once
#include <Component.h>
#include "PlayerDataComponent.h"
#include <TextComponent.h>

class LifeTrackerComponent : public boop::Component
{
public:
	LifeTrackerComponent(PlayerDataComponent* playerData, boop::TextComponent* textDisplay);

	void Update() override;

private:
	PlayerDataComponent* m_pPlayerData;
	boop::TextComponent* m_pTextDisplay;
	unsigned int m_Lives;
};

