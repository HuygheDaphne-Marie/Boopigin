#include "MenuSelectConfirmCommand.h"

#include "MenuSelectComponent.h"

MenuSelectConfirmCommand::MenuSelectConfirmCommand(MenuSelectComponent* menu)
	: m_pMenu(menu)
{
}

void MenuSelectConfirmCommand::Execute()
{
	m_pMenu->OnSelectGameMode();
}
