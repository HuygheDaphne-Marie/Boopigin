#include "MiniginPCH.h"
#include "FpsComponent.h"
#include "TextComponent.h"
#include "Time.h"

boop::FpsComponent::FpsComponent(TextComponent* linkedTextComp)
	: m_pLinkedTextComponent(linkedTextComp),
	m_MilliPassed(0),
	m_TotalFrameCount(0)
{
	if(m_pLinkedTextComponent == nullptr)
	{
		m_pLinkedTextComponent = m_pOwner->GetComponentOfType<TextComponent>();
		// todo: if it's still null now there's no TextComponent, we should throw
	}
}

void boop::FpsComponent::Update()
{
	m_MilliPassed += Time::GetInstance().GetElapsedMilli();
	m_TotalFrameCount++;

	const int fps = static_cast<int>(std::ceil(static_cast<float>(m_TotalFrameCount) / (m_MilliPassed / 1000.f)));
	
	m_pLinkedTextComponent->SetText(std::to_string(fps));
}
