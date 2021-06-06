#pragma once
#include <Command.h>
class MenuSelectComponent;

class MenuSelectChangeCommand final : public boop::Command
{
public:
	explicit MenuSelectChangeCommand(MenuSelectComponent* menu, bool goUp);
	void Execute() override;

private:
	MenuSelectComponent* m_pMenu;
	bool m_MakeSelectionGoUp;
};

