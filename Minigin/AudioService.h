#pragma once

namespace boop
{
	class AudioService
	{
	public:
		virtual ~AudioService() = default;

		virtual void PlayMusic(const std::string& filename, int volume) = 0;
		virtual void PlaySound(const std::string& filename, int volume) = 0;
	};

	class NullAudioService final : public AudioService
	{
	public:
		void PlayMusic(const std::string& filename, int volume) override {};
		void PlaySound(const std::string& filename, int volume) override {};
	};
}


