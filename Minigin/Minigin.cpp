#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <future>

#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"

#include "Time.h"

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
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	
	// Own Init
	Time::GetInstance().m_DesiredFramePerSecond = m_FixedUpdateFps;
	m_pTestCommand = new TestCommand();
	
	InputManager::GetInstance().AddCommandToButton(KeyInfo(SDLK_a), m_pTestCommand, KeyState::Pressed);
	auto* pAudioService = new SimpleSld2AudioService();
	ServiceLocator::GetInstance().RegisterAudioService(pAudioService);
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

	// Week 3
	const auto displayFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	// Player 1
	{
		// QBert (Player 1)
		go = std::make_shared<GameObject>();
		auto* pPlayerOneComponent = new PlayerComponent(ControllerButton::ButtonA, ControllerButton::ButtonB);
		go->AddComponent(pPlayerOneComponent);
		scene.Add(go);

		// Lives Display
		go = std::make_shared<GameObject>();
		go->AddComponent(new TransformComponent(10, 70));
		TextComponent* pLifeDisplayOneText = new TextComponent("Current Lives: X", displayFont);
		go->AddComponent(pLifeDisplayOneText);
		auto* pLifeDisplayOne = new LifeDisplayComponent(pPlayerOneComponent, pLifeDisplayOneText);
		go->AddComponent(pLifeDisplayOne);
		scene.Add(go);

		pPlayerOneComponent->m_pSubject->AddObserver(pLifeDisplayOne->GetObserver());

		// Score Display
		go = std::make_shared<GameObject>();
		go->AddComponent(new TransformComponent(10, 100));
		TextComponent* pScoreOneText = new TextComponent("Current Score: X", displayFont);
		go->AddComponent(pScoreOneText);
		auto* pScoreDisplayOne = new ScoreDisplayComponent(pScoreOneText);
		go->AddComponent(pScoreDisplayOne);
		scene.Add(go);

		pPlayerOneComponent->m_pSubject->AddObserver(pScoreDisplayOne->GetObserver());
	}
	
	// Player 2
	{
		// QBert
		go = std::make_shared<GameObject>();
		auto* pPlayerComponentTwo = new PlayerComponent(ControllerButton::ButtonX, ControllerButton::ButtonY);
		go->AddComponent(pPlayerComponentTwo);
		scene.Add(go);

		// Lives Display
		go = std::make_shared<GameObject>();
		go->AddComponent(new TransformComponent(10, 200));
		TextComponent* pLifeDisplayTwoText = new TextComponent("Current Lives: X", displayFont);
		go->AddComponent(pLifeDisplayTwoText);
		auto* pLifeDisplayTwo = new LifeDisplayComponent(pPlayerComponentTwo, pLifeDisplayTwoText);
		go->AddComponent(pLifeDisplayTwo);
		scene.Add(go);

		pPlayerComponentTwo->m_pSubject->AddObserver(pLifeDisplayTwo->GetObserver());

		// Score Display
		go = std::make_shared<GameObject>();
		go->AddComponent(new TransformComponent(10, 230));
		TextComponent* pScoreTextTwo = new TextComponent("Current Score: X", displayFont);
		go->AddComponent(pScoreTextTwo);
		auto* pScoreDisplayTwo = new ScoreDisplayComponent(pScoreTextTwo);
		go->AddComponent(pScoreDisplayTwo);
		scene.Add(go);

		pPlayerComponentTwo->m_pSubject->AddObserver(pScoreDisplayTwo->GetObserver());
	}

	// Controls
	go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent(10, 330));
	TextComponent* pControlText = new TextComponent("Player 1: A to die, B to gain score | Player 2: X to die, Y to gain score", displayFont);
	go->AddComponent(pControlText);
	scene.Add(go);

	ServiceLocator::GetInstance().GetAudioService()->PlaySound("../3rdParty/Simple-SDL2-Audio/sounds/door1.wav", 100);
}

void boop::Minigin::Cleanup()
{
	delete m_pTestCommand;
	
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
		Time* pTime = &Time::GetInstance();
		while (shouldContinue)
		{
			shouldContinue = input.ProcessInput();
			input.HandleInput();
			
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
