#include "MiniginPCH.h"
#include "ServiceLocator.h"

#include "AudioService.h"

boop::ServiceLocator::ServiceLocator()
	: m_pDefaultAudioService(new NullAudioService())
	, m_pAudioService(nullptr)
{
}

boop::ServiceLocator::~ServiceLocator()
{
	if (m_pAudioService != nullptr)
	{
		delete m_pAudioService;
		m_pAudioService = nullptr;
	}

	if (m_pDefaultAudioService != nullptr)
	{
		delete m_pDefaultAudioService;
		m_pDefaultAudioService = nullptr;
	}
	
}

void boop::ServiceLocator::RegisterAudioService(AudioService* pAudioService)
{
	if (pAudioService == nullptr)
	{
		if (m_pAudioService != nullptr && m_pAudioService != m_pDefaultAudioService)
		{
			delete m_pAudioService;
			m_pAudioService = nullptr;
		}
	}

	if (m_pAudioService != m_pDefaultAudioService)
	{
		delete m_pAudioService;
		m_pAudioService = pAudioService;
	}
}

boop::AudioService* boop::ServiceLocator::GetAudioService() const
{
	if (m_pAudioService == nullptr)
	{
		return m_pDefaultAudioService;
	}
	return m_pAudioService;
}


