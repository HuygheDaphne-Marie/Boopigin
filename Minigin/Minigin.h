#pragma once
#include "Game.h"

struct SDL_Window;
namespace boop
{
	class TestCommand;

	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
		
		Game* m_pGame;
		const int m_WindowWidth = 640;
		const int m_WindowHeight = 480;
	
	private:
		static const int m_FixedUpdateFps = 60;
		SDL_Window* m_Window{};
	};
}