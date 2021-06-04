#include <Minigin.h>

#include "GameSetup.h"


using namespace boop;

int main(int, char* [])
{
	Minigin engine;
	engine.m_pGame = new GameSetup(engine.m_WindowWidth, engine.m_WindowHeight);
	engine.Run();
	
	return 0;
}
