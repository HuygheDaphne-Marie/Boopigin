#include <Minigin.h>

#include "GameSetup.h"


using namespace boop;

int main(int, char* [])
{
	Minigin engine;
	engine.m_pGame = new GameSetup();
	engine.Run();
	
	return 0;
}
