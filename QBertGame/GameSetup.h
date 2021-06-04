#pragma once
#include <Game.h>

class GameSetup final : public Game
{
public:
	GameSetup(int windowWidth, int windowHeight);
	void LoadGame() const override;

	const int m_WindowWidth;
	const int m_WindowHeight;
};

