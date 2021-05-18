#include "MiniginPCH.h"
#include "LifeDisplayComponent.h"

#include "TextComponent.h"
#include "PlayerComponent.h"

boop::LifeDisplayComponent::LifeDisplayComponent(PlayerComponent* pLinkedPlayer, TextComponent* pLinkedTextComponent)
	: m_pTextComponent(pLinkedTextComponent)
	, m_PlayerComponent(pLinkedPlayer)
	, m_LivesChanged(true)
	, m_LivesLeft(0) 
	, m_pObserver(new Observer())
{
	if (m_pTextComponent == nullptr)
	{
		m_pTextComponent = m_pOwner->GetComponentOfType<TextComponent>();
		std::cerr << "Error: LifeDisplayComponent, requires it's game object to have a TextComponent\n";
	}

	m_pObserver->AddEventCallback("PlayerDied", this, &LifeDisplayComponent::OnDeath);
}

boop::LifeDisplayComponent::~LifeDisplayComponent()
{
	delete m_pObserver;
}


boop::Observer* boop::LifeDisplayComponent::GetObserver() const
{
	return m_pObserver;
}

void boop::LifeDisplayComponent::OnDeath(const Event& event)
{
	m_LivesLeft = event.GetData<int>();
	m_LivesChanged = true;
}

void boop::LifeDisplayComponent::Update()
{
	if (m_LivesChanged)
	{
		m_pTextComponent->SetText("Current lives: " + std::to_string(m_PlayerComponent->GetLives()));
		m_LivesChanged = false;
	}
}
