#include "ScoreDataComponent.h"

ScoreDataComponent::ScoreDataComponent()
	: m_Score(0)
{
	EventQueue::GetInstance().Subscribe("ScoreGained", this);
}

bool ScoreDataComponent::OnEvent(const Event& event)
{
	if (event.message == "ScoreGained")
	{
		const int amountGained = event.GetData<int>();
		m_Score += amountGained;
		return true;
	}
	return false;
}

unsigned int ScoreDataComponent::GetScore() const
{
	return m_Score;
}

void ScoreDataComponent::Reset()
{
	m_Score = 0;
}

