#pragma once
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
	private:
		static const int m_FixedUpdateFps = 60;
		SDL_Window* m_Window{};

		TestCommand* m_pTestCommand;
	};
}