#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "EventQueue.h"
#include <SDL.h>
#include <future>

#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"

#include "Timer.h"

#include <iostream>

#include "TransformComponent.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FpsComponent.h"
#include "LifeDisplayComponent.h"
#include "ScoreDisplayComponent.h"
#include "PlayerComponent.h"
#include "Subject.h"
#include "Key.h"

#include "TestCommand.h"

#include "ServiceLocator.h"
#include "AudioService.h"
#include "SimpleSLD2AudioService.h"

using namespace std;
using namespace std::chrono;
using namespace boop;

void boop::Minigin::Initialize()
{
	_putenv("SDL_AUDIODRIVER=DirectSound");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		m_WindowWidth,
		m_WindowHeight,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	/* initialize random seed: */
	srand(static_cast<unsigned int>(time(nullptr)));
	
	Renderer::GetInstance().Init(m_Window);

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	
	// Own Init
	Timer::GetInstance().m_DesiredFramePerSecond = m_FixedUpdateFps;
	
	InputManager::GetInstance();
	auto* pAudioService = new SimpleSld2AudioService();
	ServiceLocator::GetInstance().RegisterAudioService(pAudioService);
}

/**
 * Code constructing the scene world starts here
 */
void boop::Minigin::LoadGame() const
{
	if (m_pGame != nullptr)
	{
		m_pGame->LoadGame();
	}
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
	LoadGame();
	
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& eventQueue = EventQueue::GetInstance();

		bool shouldContinue = true;
		
		auto audioFuture = std::async(launch::async, [&shouldContinue]()
			{
				const auto& audio = ServiceLocator::GetInstance().GetAudioService();
				while (shouldContinue)
				{
					audio->ProcessSoundRequests();
				}
			});


		double timeSinceLastFrame = 0.0;
		Timer* pTime = &Timer::GetInstance();
		pTime->Start();
		while (shouldContinue)
		{
			shouldContinue = input.ProcessInput();
			input.HandleInput();
 
			timeSinceLastFrame += pTime->GetElapsedSec();
			
			if (timeSinceLastFrame >= pTime->GetMilliPerFrame())
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
			eventQueue.HandleQueue();
			sceneManager.GetActiveScene()->DeleteRemovedObjects();
			sceneManager.GetActiveScene()->AddObjects();
			pTime->Update();
		}
	}

	Cleanup();
}
