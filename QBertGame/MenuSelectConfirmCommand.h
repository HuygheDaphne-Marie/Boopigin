#pragma once
#include <Command.h>
class MenuSelectComponent;

class MenuSelectConfirmCommand final : public boop::Command
{
public:
	explicit MenuSelectConfirmCommand(MenuSelectComponent* menu);
	void Execute() override;

private:
	MenuSelectComponent* m_pMenu;
};

