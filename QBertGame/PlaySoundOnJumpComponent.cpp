#include "PlaySoundOnJumpComponent.h"
#include "JumpComponent.h"
#include <ServiceLocator.h>
#include <AudioService.h>

PlaySoundOnJumpComponent::PlaySoundOnJumpComponent(const std::string& soundToPlayPath)
	: m_SoundToPlay(soundToPlayPath)
{
	EventQueue::GetInstance().Subscribe("StartJump", this);
}

bool PlaySoundOnJumpComponent::OnEvent(const Event& event)
{
	if (event.message == "StartJump")
	{
		if (event.GetData<JumpComponent*>()->GetOwner() == this->GetOwner())
		{
			boop::ServiceLocator::GetInstance().GetAudioService()->PlaySound(m_SoundToPlay, 100);
			return true;
		}
	}
	return false;
}
