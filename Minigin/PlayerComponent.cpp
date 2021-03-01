#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "Subject.h"

#include "InputManager.h"
#include "DieCommand.h"
#include "ScoreCommand.h"

boop::PlayerComponent::PlayerComponent(ControllerButton dieButton, ControllerButton scoreButton)
	: m_pSubject(std::make_shared<Subject>())
	, m_pDieCommand(new DieCommand(this))
	, m_pScoreCommand(new ScoreCommand(this))
	, m_Lives(3)
{
	InputManager::GetInstance().AddCommandToButton(KeyInfo(dieButton), m_pDieCommand, KeyState::Pressed);
	InputManager::GetInstance().AddCommandToButton(KeyInfo(scoreButton), m_pScoreCommand, KeyState::Pressed);
}

boop::PlayerComponent::~PlayerComponent()
{
	delete m_pDieCommand; // Todo: Remove an entry from inputManager
	delete m_pScoreCommand;
}

void boop::PlayerComponent::Update()
{
	//if (m_FirstUpdate) //Todo: bind this to a button once I have a controller, or a key once keyboardManager is implemented
	//{
	//	// Color change
	//	ScoreGained(25);

	//	// Kill Coily
	//	ScoreGained(500);

	//	// ...
	//	
	//	m_FirstUpdate = false;
	//}
}

void boop::PlayerComponent::OnDeath()
{
	m_Lives--;
	m_pSubject->Notify(Event("PlayerDied", m_Lives));
}
void boop::PlayerComponent::ScoreGained(int amount) const
{
	m_pSubject->Notify(Event("ScoreGained", amount));
}

int boop::PlayerComponent::GetLives() const
{
	return m_Lives;
}
