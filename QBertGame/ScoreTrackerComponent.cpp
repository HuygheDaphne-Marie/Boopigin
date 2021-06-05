#include "ScoreTrackerComponent.h"
#include <string>

ScoreTrackerComponent::ScoreTrackerComponent(ScoreDataComponent* scoreData, boop::TextComponent* textDisplay)
	: m_pScoreData(scoreData)
	, m_pTextDisplay(textDisplay)
	, m_Score(0)
{
}

void ScoreTrackerComponent::Startup()
{
	if (m_pTextDisplay == nullptr)
	{
		m_pTextDisplay = m_pOwner->GetComponentOfType<boop::TextComponent>();
	}
	m_pTextDisplay->SetText("Score: " + std::to_string(m_Score));
}

void ScoreTrackerComponent::Update()
{
	if (m_pScoreData->GetScore() != m_Score)
	{
		m_Score = m_pScoreData->GetScore();
		m_pTextDisplay->SetText("Score: " + std::to_string(m_Score));
	}
}
