#include "MiniginPCH.h"
#include "Timer.h"


boop::Timer::Timer()
	: m_DesiredFramePerSecond(60),
	m_PreviousTime(std::chrono::high_resolution_clock::now()),
	m_TimeSinceLastFrame(0.0),
	m_ElapsedSeconds(0.f)
{
}

void boop::Timer::Start()
{
	m_PreviousTime = std::chrono::high_resolution_clock::now();
}

void boop::Timer::Update()
{
	m_StartTime = std::chrono::steady_clock::now();
	m_ElapsedSeconds = std::chrono::duration<float>(m_StartTime - m_PreviousTime).count();
	
	m_PreviousTime = m_StartTime;
}

int boop::Timer::GetElapsedMilli() const
{
	return static_cast<int>(m_ElapsedSeconds) * 1000;
}

float boop::Timer::GetElapsedSec() const
{
	return m_ElapsedSeconds;
}

float boop::Timer::GetMilliPerFrame() const
{
	return 1000.f / static_cast<float>(m_DesiredFramePerSecond);
}

