#include "MiniginPCH.h"
#include "SimpleSLD2AudioService.h"

#include <SDL.h>
#include "../3rdParty/Simple-SDL2-Audio/src/audio.h"

boop::SimpleSLD2AudioService::SimpleSLD2AudioService()
{
	SDL_Init(SDL_INIT_AUDIO);
	initAudio();
}

void boop::SimpleSLD2AudioService::PlayMusic(const std::string& filename, int volumePercentage)
{
	playMusic("music/highlands.wav", GetAbsoluteVolumeFromPercentage(volumePercentage));
}

void boop::SimpleSLD2AudioService::PlaySound(const std::string& filename, int volumePercentage)
{
	playSound("music/highlands.wav", GetAbsoluteVolumeFromPercentage(volumePercentage));
}

int boop::SimpleSLD2AudioService::GetAbsoluteVolumeFromPercentage(int volumePercentage)
{
	if (volumePercentage < 0)
	{
		volumePercentage = 0;
	}
	if (volumePercentage > 100)
	{
		volumePercentage = 100;
	}
	return static_cast<int>(static_cast<float>(SDL_MIX_MAXVOLUME) / 100.f * static_cast<float>(volumePercentage));
}
