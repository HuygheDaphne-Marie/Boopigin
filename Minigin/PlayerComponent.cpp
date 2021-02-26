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

void boop::PlayerComponent::Update()
{
	if (m_FirstUpdate) //Todo: bind this to a button once I have a controller, or a key once keyboardManager is implemented
	{
		// Color change
		OnScoreGained(25);

		// Kill Coily
		OnScoreGained(500);

		// ...
		
		m_FirstUpdate = false;
	}
}

void boop::PlayerComponent::OnDeath()
{
	m_Lives--;
	m_pSubject->Notify(Event("PlayerDied", m_Lives));
}
void boop::PlayerComponent::OnScoreGained(int amount) const
{
	m_pSubject->Notify(Event("ScoreGained", amount));
}

int boop::PlayerComponent::GetLives() const
{
	return m_Lives;
}
