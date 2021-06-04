#include "PlayerDataComponent.h"

PlayerDataComponent::PlayerDataComponent(const unsigned lives)
	: m_LivesStartAmount(lives)
	, m_Lives(lives)
{
	EventQueue::GetInstance().Subscribe("PlayerTakeDamage", this);
}

unsigned PlayerDataComponent::GetLives() const
{
	return m_Lives;
}

void PlayerDataComponent::LoseLife()
{
	if (m_Lives > 0)
	{
		m_Lives--;
	}
}

void PlayerDataComponent::Reset()
{
	m_Lives = m_LivesStartAmount;
}

void PlayerDataComponent::Update()
{
	if (m_Lives == 0)
	{
		EventQueue::GetInstance().Broadcast(new Event("PlayerDied"));
	}
}

bool PlayerDataComponent::OnEvent(const Event& event)
{
	if (event.message == "PlayerTakeDamage")
	{
		if (event.GetData<boop::GameObject*>() == m_pOwner)
		{
			LoseLife();
			return true;
		}
	}
	return false;
}
