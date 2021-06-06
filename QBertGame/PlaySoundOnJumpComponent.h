#pragma once
#include <Component.h>
#include <IEventListener.h>
#include <string>

class PlaySoundOnJumpComponent : public boop::Component, public IEventListener
{
public:
	explicit PlaySoundOnJumpComponent(const std::string& soundToPlayPath);
	bool OnEvent(const Event& event) override;

private:
	const std::string m_SoundToPlay;
};

