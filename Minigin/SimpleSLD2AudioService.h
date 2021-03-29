#pragma once
#include "AudioService.h"
#include "../3rdParty/Simple-SDL2-Audio/src/audio.h"
#include <queue>
#include <mutex>

namespace boop
{
	class SimpleSld2AudioService final : public AudioService
	{
	public:
		SimpleSld2AudioService();
		SimpleSld2AudioService(const SimpleSld2AudioService& other) = delete;
		SimpleSld2AudioService(SimpleSld2AudioService&& other) = delete;
		SimpleSld2AudioService operator=(const SimpleSld2AudioService& other) = delete;
		SimpleSld2AudioService operator=(SimpleSld2AudioService&& other) = delete;
		~SimpleSld2AudioService();

		// Possibly misleading name: Adds a request to play this music/sound to the queue (Need to conform to Interface)
		void PlayMusic(const std::string& filename, int volumePercentage) override;
		void PlaySound(const std::string& filename, int volumePercentage) override;

		void ProcessSoundRequests() override;

	private:
		enum class AudioType
		{
			sound,
			music
		};
		struct AudioRequest
		{
			const AudioType audioType;
			const std::string filename;
			int volumePercentage;
		};

		std::queue<AudioRequest> m_SoundRequestQueue;
		std::mutex m_Mutex;
		
		static int GetAbsoluteVolumeFromPercentage(int volumePercentage);
	};
}

