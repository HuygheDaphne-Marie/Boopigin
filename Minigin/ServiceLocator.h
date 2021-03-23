#pragma once
#include "Singleton.h"

namespace boop
{
	class AudioService;

	class ServiceLocator final : public Singleton<ServiceLocator>
	{
	public:
		ServiceLocator(const ServiceLocator& other) = delete;
		ServiceLocator(ServiceLocator&& other) = delete;
		ServiceLocator& operator=(const ServiceLocator& other) = delete;
		ServiceLocator& operator=(ServiceLocator&& other) = delete;
		~ServiceLocator();

		void RegisterAudioService(AudioService* pAudioService);
		[[nodiscard]] AudioService* GetAudioService() const;

	private:
		friend class Singleton<ServiceLocator>;
		ServiceLocator();

		AudioService* m_pAudioService;
		AudioService* m_pDefaultAudioService;
	};
}

