#pragma once
#include "AudioService.h"

namespace boop
{
	class SimpleSLD2AudioService final : public AudioService
	{
	public:
		SimpleSLD2AudioService();
		
		void PlayMusic(const std::string& filename, int volumePercentage) override;
		void PlaySound(const std::string& filename, int volumePercentage) override;

	private:
		int GetAbsoluteVolumeFromPercentage(int volumePercentage);
	};
}

