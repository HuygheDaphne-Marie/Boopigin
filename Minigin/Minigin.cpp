#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"

#include "Time.h"

#include "TransformComponent.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FpsComponent.h"

using namespace std;
using namespace std::chrono;
using namespace boop;

void boop::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	// Own Init
	Time::GetInstance().m_DesiredFramePerSecond = m_FixedUpdateFps;
}

/**
 * Code constructing the scene world starts here
 */
void boop::Minigin::LoadGame() const
{
	// Load this all from a file later cause this is very hard coded **Yikers**
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent(0, 0));
	go->AddComponent(new TextureComponent("background.jpg"));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent(216, 180));
	go->AddComponent(new TextureComponent("logo.png"));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent(80, 20));
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent(new TextComponent("Programming 4 Assignment", font));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent(10, 10));
	const auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	TextComponent* pFpsTextComponent = new TextComponent("TEMP", fpsFont);
	go->AddComponent(pFpsTextComponent);
	go->AddComponent(new FpsComponent(pFpsTextComponent));
	scene.Add(go);
}

void boop::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void boop::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool shouldContinue = true;

		double timeSinceLastFrame = 0.0;
		Time* pTime = &Time::GetInstance();
		while (shouldContinue)
		{
			shouldContinue = input.ProcessInput();
			
			timeSinceLastFrame += pTime->GetElapsedMilli();
			while (timeSinceLastFrame >= pTime->GetMilliPerFrame())
			{
				// Fixed Update, for physics & networking
				sceneManager.FixedUpdate();
				timeSinceLastFrame -= pTime->GetMilliPerFrame();
			}

			// Update, this should be used by default
			sceneManager.Update();

			// Late Update, this should be used for things that depend on something which might change in update
			sceneManager.LateUpdate();
			
			renderer.Render();
		}
	}

	Cleanup();
}
