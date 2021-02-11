#include "MiniginPCH.h"
#include "Time.h"


boop::Time::Time()
	: m_DesiredFramePerSecond(60),
	m_PreviousTime(std::chrono::high_resolution_clock::now()),
	m_TimeSinceLastFrame(0)
{
}

void boop::Time::Start()
{
	m_PreviousTime = std::chrono::high_resolution_clock::now();
}

void boop::Time::Update()
{
	m_PreviousTime = std::chrono::high_resolution_clock::now();
}

float boop::Time::GetElapsedMilli() const
{
	const auto currentTime = std::chrono::high_resolution_clock::now();
	const auto elapsedTime = currentTime - m_PreviousTime;
	return static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime).count());
}

float boop::Time::GetMilliPerFrame() const
{
	return 1000.f / static_cast<float>(m_DesiredFramePerSecond);
}

