#include "MiniginPCH.h"
#include "SimpleSLD2AudioService.h"

#include <SDL.h>
#include "../3rdParty/Simple-SDL2-Audio/src/audio.c"

boop::SimpleSLD2AudioService::SimpleSLD2AudioService()
{
	//SDL_Init(SDL_INIT_AUDIO);
	initAudio();
}

boop::SimpleSLD2AudioService::~SimpleSLD2AudioService()
{
	endAudio();
}

void boop::SimpleSLD2AudioService::PlayMusic(const std::string& filename, int volumePercentage)
{
	playMusic(filename.c_str(), GetAbsoluteVolumeFromPercentage(volumePercentage));
}

void boop::SimpleSLD2AudioService::PlaySound(const std::string& filename, int volumePercentage)
{
	playSound(filename.c_str(), GetAbsoluteVolumeFromPercentage(volumePercentage));
	std::cout << SDL_GetError();
}

int boop::SimpleSLD2AudioService::GetAbsoluteVolumeFromPercentage(int volumePercentage)
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
