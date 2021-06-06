#pragma once
#include <Component.h>
#include <memory>
#include <vector>
#include "LevelComponent.h"
#include "MenuSelectChangeCommand.h"
#include "MenuSelectConfirmCommand.h"

class MenuSelectComponent : public boop::Component
{
public:
	explicit MenuSelectComponent(LevelComponent* pLevel);
	~MenuSelectComponent() override;
	
	void AddButton(std::shared_ptr<boop::GameObject> button);

	void OnSelectChange(bool goUp);
	void OnSelectGameMode();
	void AddSelector(const std::shared_ptr<boop::GameObject>& selector);

	void Startup() override;

private:
	std::vector<std::shared_ptr<boop::GameObject>> m_Buttons{};
	int m_CurrentlySelectedIndex = 0;

	LevelComponent* m_pLevel;
	std::shared_ptr<boop::GameObject> m_Selector;

	MenuSelectChangeCommand* m_pGoUpCommand;
	MenuSelectChangeCommand* m_pGoDownCommand;
	MenuSelectConfirmCommand* m_pConfirmCommand;

	void UpdateSelectorPos();
};




