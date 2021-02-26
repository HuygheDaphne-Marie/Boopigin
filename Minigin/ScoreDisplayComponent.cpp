#include "MiniginPCH.h"
#include "ScoreDisplayComponent.h"

#include "TextComponent.h"
#include "Observer.h"
#include "Event.h"

boop::ScoreDisplayComponent::ScoreDisplayComponent(TextComponent* pLinkedTextComponent)
	: m_pTextComponent(pLinkedTextComponent)
	, m_pObserver(new Observer())
	, m_ScoreChanged(true)
	, m_Score(0)
{
	if (m_pTextComponent == nullptr)
	{
		m_pTextComponent = m_pOwner->GetComponentOfType<TextComponent>();
		// todo: if it's still null now there's no TextComponent, we should throw
	}

	m_pObserver->AddEventCallback("ScoreGained", this, &ScoreDisplayComponent::OnScoreGained);
}
boop::ScoreDisplayComponent::~ScoreDisplayComponent()
{
	delete m_pObserver;
}

void boop::ScoreDisplayComponent::OnScoreGained(const Event& event)
{
	m_Score += static_cast<EventData<int>*>(event.pEventData)->data;
	m_ScoreChanged = true;
}

void boop::ScoreDisplayComponent::Update()
{
	if (m_ScoreChanged)
	{
		m_pTextComponent->SetText("Score: " + std::to_string(m_Score));
		m_ScoreChanged = false;
	}
}

boop::Observer* boop::ScoreDisplayComponent::GetObserver() const
{
	return m_pObserver;
}
