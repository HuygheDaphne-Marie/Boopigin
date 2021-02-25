#include "MiniginPCH.h"
#include "DisplayLivesComponent.h"

#include "TextComponent.h"
#include "PlayerComponent.h"

boop::DisplayLivesComponent::DisplayLivesComponent(PlayerComponent* pLinkedPlayer, TextComponent* pLinkedTextComponent)
	: m_pTextComponent(pLinkedTextComponent)
	, m_PlayerComponent(pLinkedPlayer)
	, m_LivesChanged(true)
	, m_pObserver(new Observer())
{
	if (m_pTextComponent == nullptr)
	{
		m_pTextComponent = m_pOwner->GetComponentOfType<TextComponent>();
		// todo: if it's still null now there's no TextComponent, we should throw
	}

	m_pObserver->AddEventCallback("PlayerDied", this, &DisplayLivesComponent::OnDeath);
}

boop::Observer* boop::DisplayLivesComponent::GetObserver() const
{
	return m_pObserver;
}

void boop::DisplayLivesComponent::OnDeath()
{
		m_LivesChanged = true;
}

void boop::DisplayLivesComponent::Update()
{
	if (m_LivesChanged)
	{
		m_pTextComponent->SetText("Current lives: " + std::to_string(m_PlayerComponent->GetLives()));
		m_LivesChanged = false;
	}
}
