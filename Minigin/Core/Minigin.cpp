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


void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1050,
		850,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}


//36

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto scene = std::make_shared<Scene>("Demo");
	SceneManager::GetInstance().AddScene(scene);

	auto background = scene->AddNew<BaseObject>();
	background->AddComponent(std::make_shared<TextureComp>("background.jpg"));

	{
	auto Bo = std::make_shared<BaseObject>();
	Bo->AddComponent(std::make_shared<TextureComp>("logo.png"));
	
	Bo->Tset(216.f, 180,90);
	scene->Add(Bo);
	}

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	{
	auto title = std::make_shared<BaseObject>();
	title->Tset(80, 20);

	title->CreateChildComponent<TextComp>("Programming 4:", font, SDL_Color{ 255,255, 255 });
	auto subTitle=title->CreateChildComponent<TextComp>("Return of the Bools", font, SDL_Color{ 255, 150, 150 });
	subTitle->SetOffset(80,50);
	scene->Add(title);}
		

	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	auto fpsObject = std::make_shared<BaseObject>();
	fpsObject->AddComponent(std::make_shared<FpsComp>(fpsFont));
	fpsObject->Tset(100, 100,100);

	//auto fpsChild = std::make_shared<BaseObject>();
	auto fpsChild = fpsObject->CreateChildObj<BaseObject>();

	fpsChild->Tset(0,40,0);
	fpsChild->AddComponent(std::make_shared<FpsComp>(fpsFont));
	fpsChild->CreateChildComponent<player1_movement_comp>();


	fpsObject->AddChild(fpsChild);

	scene->Add(fpsObject);

	auto level = std::make_shared<LevelObject>("../Data/Map2.csv");
	scene->Add(level);
}

void dae::Minigin::Cleanup()
{
	InputManager::GetInstance().Destroy();
	Renderer::GetInstance().Destroy();
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
