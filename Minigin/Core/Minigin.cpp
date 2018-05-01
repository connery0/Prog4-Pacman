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
#include "../ObjComp/TransformComponent.h"


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
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto scene = new Scene("Demo");
	SceneManager::GetInstance().AddScene(scene);

	scene->Add((new BaseObject())->AddComponent(new TextureComp("background.jpg")));

	auto Bo = new BaseObject();
	Bo->AddComponent(new TextureComp("logo.png"));
	Bo->T()->SetPosition(216.f, 180);
	scene->Add(Bo);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);


	auto title = new BaseObject();
	title->T()->SetPosition(80, 20);
	auto text1 = new TextComp("Programming 4:", font, { 255,255, 255 });
	auto text2 = new TextComp("Return of the Bools", font, { 255, 150, 150 });
	text2->SetOffset(80, 50);
	title->AddComponent(text1)->AddComponent(text2);
	scene->Add(title);



	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto fps = new FpsComp(fpsFont);
	scene->Add((new BaseObject())->AddComponent(fps));

}

void dae::Minigin::Cleanup()
{
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
	while (docontinue)
	{
		auto currenttime = std::chrono::high_resolution_clock::now();
		float deltatime = std::chrono::duration<float>(currenttime - lasttime).count();
		lasttime = currenttime;
		docontinue = input.ProcessInput();

		scenemanager.Update(deltatime);
		renderer.Render();
	}

	Cleanup();
}
