#include "MenuSelectComponent.h"
#include <TransformComponent.h>
#include <TextComponent.h>
#include <SceneManager.h>

#include <InputManager.h>
#include <Key.h>

MenuSelectComponent::MenuSelectComponent(LevelComponent* pLevel)
	: m_pLevel(pLevel)
{
	m_pGoUpCommand = new MenuSelectChangeCommand(this, true);
	m_pGoDownCommand = new MenuSelectChangeCommand(this, false);
	boop::InputManager::GetInstance().AddCommandToButton(boop::KeyInfo(SDLK_UP), m_pGoUpCommand, boop::KeyState::Pressed);
	boop::InputManager::GetInstance().AddCommandToButton(boop::KeyInfo(SDLK_DOWN), m_pGoDownCommand, boop::KeyState::Pressed);

	m_pConfirmCommand = new MenuSelectConfirmCommand(this);
	boop::InputManager::GetInstance().AddCommandToButton(boop::KeyInfo(SDLK_SPACE), m_pConfirmCommand, boop::KeyState::Pressed);
}

MenuSelectComponent::~MenuSelectComponent()
{
	delete m_pGoUpCommand;
	delete m_pGoDownCommand;
	delete m_pConfirmCommand;
}

void MenuSelectComponent::AddButton(std::shared_ptr<boop::GameObject> button)
{
	if (std::find(m_Buttons.begin(), m_Buttons.end(), button) == m_Buttons.end())
	{
		m_Buttons.push_back(button);
	}
}

void MenuSelectComponent::OnSelectChange(bool goUp)
{
	if (goUp && m_CurrentlySelectedIndex > 0)
		m_CurrentlySelectedIndex--;
	else if(!goUp && m_CurrentlySelectedIndex < static_cast<int>(m_Buttons.size()) -1)
		m_CurrentlySelectedIndex++;

	UpdateSelectorPos();
}

void MenuSelectComponent::OnSelectGameMode()
{
	if (m_Buttons[m_CurrentlySelectedIndex]->HasTag("single"))
	{
		m_pLevel->SetGameMode(GameMode::single);
	}

	if (m_Buttons[m_CurrentlySelectedIndex]->HasTag("coop"))
	{
		m_pLevel->SetGameMode(GameMode::coop);
	}

	if (m_Buttons[m_CurrentlySelectedIndex]->HasTag("versus"))
	{
		m_pLevel->SetGameMode(GameMode::versus);
	}

	boop::SceneManager::GetInstance().SetSceneAsActive("game");
}

void MenuSelectComponent::AddSelector(const std::shared_ptr<boop::GameObject>& selector)
{
	m_Selector = selector;
}

void MenuSelectComponent::Startup()
{
	UpdateSelectorPos();
}

void MenuSelectComponent::UpdateSelectorPos()
{
	auto selectorTransform = m_Selector->GetComponentOfType<boop::TransformComponent>();
	const auto selectorText = m_Selector->GetComponentOfType<boop::TextComponent>();
	const auto btnTransform = m_Buttons[m_CurrentlySelectedIndex]->GetComponentOfType<boop::TransformComponent>();

	auto btnPos = btnTransform->GetPosition();
	btnPos.x -= selectorText->GetWidth() * 2;
	selectorTransform->SetPosition(btnPos.x, btnPos.y);
}
