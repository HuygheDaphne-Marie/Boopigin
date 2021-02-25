#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "Subject.h"

#include "InputManager.h"
#include "DieCommand.h"

boop::PlayerComponent::PlayerComponent()
	: m_pSubject(std::make_shared<Subject>())
	, m_pDieCommand(new DieCommand(this))
{
	InputManager::GetInstance().AddCommandToButton(KeyInfo(ControllerButton::ButtonA), m_pDieCommand, KeyState::Pressed);
}

boop::PlayerComponent::~PlayerComponent()
{
	delete m_pDieCommand;
}

void boop::PlayerComponent::OnDeath() const
{
	m_pSubject->Notify("PlayerDied");
}
