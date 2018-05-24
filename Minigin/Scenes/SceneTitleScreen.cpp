#include "MiniginPCH.h"
#include "SceneTitleScreen.h"
#include "../ObjComp/LevelObject.h"
#include "../ObjComp/FpsComp.h"
#include "../ObjComp/TextureComp.h"
#include "../ObjComp/Player1MovementComp.h"


SceneTitleScreen::SceneTitleScreen(): Scene("TitleScene")
{
}


SceneTitleScreen::~SceneTitleScreen()
{
}

void SceneTitleScreen::Initialize()
{
	auto background = AddNew<BaseObject>();
	background->AddComponent(std::make_shared<dae::TextureComp>("background.jpg"));
	{
		auto Bo = std::make_shared<BaseObject>();
		Bo->AddComponent(std::make_shared<dae::TextureComp>("logo.png"));

		Bo->Tset(216.f, 180, 90);
		Add(Bo);
	}

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	{
		auto title = std::make_shared<BaseObject>();
		title->Tset(80, 20);

		title->CreateChildComponent<TextComp>("Programming 4:", font, SDL_Color{ 255,255, 255 });
		auto subTitle = title->CreateChildComponent<TextComp>("Return of the Bools", font, SDL_Color{ 255, 150, 150 });
		subTitle->SetOffset(80, 50);
		Add(title); }


	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	auto fpsObject = std::make_shared<BaseObject>();
	fpsObject->AddComponent(std::make_shared<dae::FpsComp>(fpsFont));
	fpsObject->Tset(100, 100, 100);

	//auto fpsChild = std::make_shared<BaseObject>();
	auto fpsChild = fpsObject->CreateChildObj<BaseObject>();

	fpsChild->Tset(0, 40, 0);
	fpsChild->AddComponent(std::make_shared<dae::FpsComp>(fpsFont));
	fpsChild->CreateChildComponent<player1_movement_comp>();


	fpsObject->AddChild(fpsChild);

	Add(fpsObject);
}
