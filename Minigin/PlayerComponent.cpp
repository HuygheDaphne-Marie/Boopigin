#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "Subject.h"

#include "InputManager.h"
#include "DieCommand.h"

boop::PlayerComponent::PlayerComponent()
	: m_pSubject(std::make_shared<Subject>())
	, m_pDieCommand(new DieCommand(this))
	, m_Lives(3)
{
	InputManager::GetInstance().AddCommandToButton(KeyInfo(ControllerButton::ButtonA), m_pDieCommand, KeyState::Pressed);
}

boop::PlayerComponent::~PlayerComponent()
{
	delete m_pDieCommand;
}

void boop::PlayerComponent::OnDeath()
{
	m_Lives--;
	m_pSubject->Notify("PlayerDied");
}

int boop::PlayerComponent::GetLives() const
{
	return m_Lives;
}
