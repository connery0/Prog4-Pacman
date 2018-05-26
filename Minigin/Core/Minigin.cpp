#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>

#include "../Scenes/SceneManager.h"

//todo: make general component include
#include "../ObjComp/BaseComponent.h"
#include "../ObjComp/TextComp.h"
#include "../ObjComp/FpsComp.h"
#include "../ObjComp/TextureComp.h"
#include "../Scenes/Scene.h"
#include "../ObjComp/BaseObject.h"
#include "../ObjComp/LevelObject.h"
#include "../ObjComp/Transform.h"
#include "../ObjComp/Player1MovementComp.h"
#include "../ObjComp/LevelObject.h"
#include "../Scenes/SceneSinglePlayerMap2.h"
#include "../Scenes/SceneTitleScreen.h"


void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	int width = 1050;
	int height=850;

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
	Renderer::GetInstance().Init(window);
	Renderer::WINDOW_WIDTH = width;
	Renderer::WINDOW_HEIGHT= height;
}


//36

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	SceneManager::GetInstance().AddScene(std::make_shared<SceneTitleScreen>());
}

void dae::Minigin::Cleanup()
{
	InputManager::GetInstance().Destroy();
	Renderer::GetInstance().Destroy();
	SceneManager::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	auto& renderer = dae::Renderer::GetInstance();
	auto& scenemanager = SceneManager::GetInstance();
	auto& input = dae::InputManager::GetInstance();

	auto lasttime = std::chrono::high_resolution_clock::now();

	bool docontinue = true;
	bool* thisIsATestBool =nullptr;
	input.AddInput('A',&thisIsATestBool);

	bool* thisIsATestBool2 = nullptr;
	input.AddInput('S', &thisIsATestBool2);

	while (docontinue)
	{
		auto currenttime = std::chrono::high_resolution_clock::now();
		float deltatime = std::chrono::duration<float>(currenttime - lasttime).count();
		lasttime = currenttime;
		input.Update();
		docontinue = input.ProcessInput();
		
		if(thisIsATestBool &&*thisIsATestBool)
		{
			input.RemoveInput(&thisIsATestBool);
			std::cout<<"TEST";
		}
		if (thisIsATestBool2 &&*thisIsATestBool2)
		{
			input.RemoveInput(&thisIsATestBool2);
			std::cout << "TEST2";
		}
		scenemanager.Update(deltatime);
		renderer.Render();
	}

	Cleanup();
}
