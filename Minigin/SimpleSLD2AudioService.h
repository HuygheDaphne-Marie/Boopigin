#pragma once
#include "AudioService.h"
#include "../3rdParty/Simple-SDL2-Audio/src/audio.h"

namespace boop
{
	class SimpleSLD2AudioService final : public AudioService
	{
	public:
		SimpleSLD2AudioService();
		~SimpleSLD2AudioService();
		
		void PlayMusic(const std::string& filename, int volumePercentage) override;
		void PlaySound(const std::string& filename, int volumePercentage) override;

	private:
		int GetAbsoluteVolumeFromPercentage(int volumePercentage);
	};
}

