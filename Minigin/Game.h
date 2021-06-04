#pragma once
//class Minigin;

class Game
{
public:
	virtual ~Game() = default;
	virtual void LoadGame() const = 0;

	//Minigin* m_pEngine = nullptr;
};

