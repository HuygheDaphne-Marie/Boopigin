#include "MenuSelectChangeCommand.h"
#include "MenuSelectComponent.h"

MenuSelectChangeCommand::MenuSelectChangeCommand(MenuSelectComponent* menu, bool goUp)
	: m_pMenu(menu)
	, m_MakeSelectionGoUp(goUp)
{
}

void MenuSelectChangeCommand::Execute()
{
	m_pMenu->OnSelectChange(m_MakeSelectionGoUp);
}
