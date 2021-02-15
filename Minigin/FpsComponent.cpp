#include "MiniginPCH.h"
#include "FpsComponent.h"
#include "TextComponent.h"
#include "Time.h"
//#include "Time.h"


boop::FpsComponent::FpsComponent(TextComponent* linkedTextComp)
	: m_pLinkedTextComponent(linkedTextComp),
	//m_MilliPassed(0),
	m_StartTime(std::chrono::high_resolution_clock::now()),
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
	const auto duration = std::chrono::high_resolution_clock::now() - m_StartTime;
	const float secondsPassedSinceStart = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() / 1000.f);
	m_TotalFrameCount++;

	const int fps = static_cast<int>(static_cast<float>(m_TotalFrameCount) / secondsPassedSinceStart);
	
	m_pLinkedTextComponent->SetText(std::to_string(fps));
}
