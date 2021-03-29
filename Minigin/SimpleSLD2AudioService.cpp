#include "MiniginPCH.h"
#include "SimpleSLD2AudioService.h"

#include <SDL.h>
#include "../3rdParty/Simple-SDL2-Audio/src/audio.c"

boop::SimpleSld2AudioService::SimpleSld2AudioService()
{
	//SDL_Init(SDL_INIT_AUDIO);
	initAudio();
}

boop::SimpleSld2AudioService::~SimpleSld2AudioService()
{
	for (auto audioPair : m_AudioMap)
	{
		freeAudio(audioPair.second);
	}
	endAudio();
}

void boop::SimpleSld2AudioService::PlayMusic(const std::string& filename, int volumePercentage)
{
	std::lock_guard<std::mutex> lock{ m_Mutex };
	m_SoundRequestQueue.push(AudioRequest{ AudioType::music, filename, volumePercentage });
}

void boop::SimpleSld2AudioService::PlaySound(const std::string& filename, int volumePercentage)
{
	std::lock_guard<std::mutex> lock{ m_Mutex };
	m_SoundRequestQueue.push(AudioRequest{ AudioType::sound, filename, volumePercentage });
}

void boop::SimpleSld2AudioService::ProcessSoundRequests()
{
	do
	{
		std::lock_guard<std::mutex> lock{ m_Mutex };
		if (m_SoundRequestQueue.empty())
		{
			continue;
		}
		
		AudioRequest request = m_SoundRequestQueue.front();
		m_SoundRequestQueue.pop();

		auto findResult = m_AudioMap.find(request.filename);
		if (findResult == m_AudioMap.end())
		{
			AddNewAudioToSavedAudio(request);
		}
		
		if (request.audioType == AudioType::music)
		{
			playMusicFromMemory(m_AudioMap[request.filename], request.volumePercentage);
		}
		else
		{
			playSoundFromMemory(m_AudioMap[request.filename], request.volumePercentage);
		}
	}
	while (!m_SoundRequestQueue.empty());
}

int boop::SimpleSld2AudioService::GetAbsoluteVolumeFromPercentage(int volumePercentage)
{
	if (volumePercentage < 0)
	{
		volumePercentage = 0;
	} else if (volumePercentage > 100)
	{
		volumePercentage = 100;
	}
	return static_cast<int>(static_cast<float>(SDL_MIX_MAXVOLUME) / 100.f * static_cast<float>(volumePercentage));
}

void boop::SimpleSld2AudioService::AddNewAudioToSavedAudio(const AudioRequest& newAudioRequest)
{
	Audio* pAudio = createAudio(newAudioRequest.filename.c_str(), static_cast<uint8_t>(newAudioRequest.audioType), 100);
	m_AudioMap.insert({ newAudioRequest.filename, pAudio });
}
