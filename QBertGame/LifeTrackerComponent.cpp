#include "LifeTrackerComponent.h"
#include <string>

LifeTrackerComponent::LifeTrackerComponent(PlayerDataComponent* playerData, boop::TextComponent* textDisplay)
	: m_pPlayerData(playerData)
	, m_pTextDisplay(textDisplay)
	, m_Lives(0)
{
}

void LifeTrackerComponent::Update()
{
	if (m_pPlayerData->GetLives() != m_Lives)
	{
		m_Lives = m_pPlayerData->GetLives();
		m_pTextDisplay->SetText("Lives left: " + std::to_string(m_Lives));
	}
}
