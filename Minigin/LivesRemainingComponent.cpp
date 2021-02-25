#include "MiniginPCH.h"
#include "LivesRemainingComponent.h"

#include "TextComponent.h"

boop::LivesRemainingComponent::LivesRemainingComponent(TextComponent* pLinkedTextComponent)
	: m_pTextComponent(pLinkedTextComponent)
	, m_LivesChanged(true) 
	, m_LivesLeft(0)
{
	if (m_pTextComponent == nullptr)
	{
		m_pTextComponent = m_pOwner->GetComponentOfType<TextComponent>();
		// todo: if it's still null now there's no TextComponent, we should throw
	}
}

void boop::LivesRemainingComponent::Update()
{
	if (m_LivesChanged)
	{
		m_pTextComponent->SetText("Current lives: " + std::to_string(m_LivesLeft));
		m_LivesChanged = false;
	}
}

void boop::LivesRemainingComponent::OnNotify(const std::string& message)
{
	if (message == "PlayerDied")
	{
		if (m_LivesLeft > 0)
		{
			m_LivesLeft--;
			m_LivesChanged = true;
		}
	}
}

void boop::LivesRemainingComponent::OnAdd()
{
}

void boop::LivesRemainingComponent::OnRemove()
{
}
