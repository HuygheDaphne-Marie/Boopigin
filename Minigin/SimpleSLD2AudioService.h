#pragma once
#include "AudioService.h"
#include "../3rdParty/Simple-SDL2-Audio/src/audio.h"
#include <queue>
#include <mutex>
#include <map>

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
			sound = 0,
			music = 1
		};
		struct AudioRequest
		{
			const AudioType audioType;
			const std::string filename;
			int volumePercentage;
		};

		std::mutex m_Mutex;
		std::queue<AudioRequest> m_SoundRequestQueue;
		std::map<std::string, Audio*> m_AudioMap;
		
		static int GetAbsoluteVolumeFromPercentage(int volumePercentage);
		void AddNewAudioToSavedAudio(const AudioRequest& newAudioRequest);
	};
}

