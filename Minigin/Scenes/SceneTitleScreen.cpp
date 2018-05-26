#include "MiniginPCH.h"
#include "SceneTitleScreen.h"
#include "../ObjComp/LevelObject.h"
#include "../ObjComp/FpsComp.h"
#include "../ObjComp/TextureComp.h"
#include "../ObjComp/Player1MovementComp.h"
#include "../ObjComp/ButtonComp.h"
#include "../Core/Renderer.h"


SceneTitleScreen::SceneTitleScreen(): Scene("TitleScene")
{
}


SceneTitleScreen::~SceneTitleScreen()
{
}

void SceneTitleScreen::Initialize()
{
	auto background = AddNew<BaseObject>();
	background->CreateChildComponent<dae::TextureComp>("background.jpg",false);

	auto title = AddNew<BaseObject>();
	title->CreateChildComponent<dae::TextureComp>("Title.png");
	title->T()->SetPosition(525.f,100.f);


	std::shared_ptr<BaseObject>TempObjectRef;
	std::shared_ptr<BaseObject>TempButtonComponentRef;

	auto LevelSelect = AddNew<BaseObject>();
	LevelSelect->CreateChildComponent<dae::TextureComp>("LevelTitle.png");
	LevelSelect->T()->SetPosition(300.f,200.f);
	LevelSelectGroup= LevelSelect->CreateChildComponent<ButtonGroupComp>();
	TempObjectRef = LevelSelect->CreateChildObj<BaseObject>();
	TempObjectRef->T()->SetPosition(100,0);
	TempButtonComponentRef= TempObjectRef->CreateChildComponent<ButtonComp>("Level 1");
	



	auto UIButtons = AddNew<BaseObject>();
	UIButtons->T()->SetPosition(dae::Renderer::WINDOW_WIDTH / 2.f, dae::Renderer::WINDOW_HEIGHT / 2.f);
	auto buttonGroup = UIButtons->CreateChildComponent<ButtonGroupComp>();
	auto Obutton1 = UIButtons->CreateChildObj<BaseObject>();

	auto button1 = Obutton1->CreateChildComponent<ButtonComp>("Button1");
	Obutton1->CreateChildComponent<dae::TextureComp>("Level1.png");
	buttonGroup->linkButton(button1)->setGroup(buttonGroup);
	Obutton1->T()->SetPosition(-100, 0);

	auto Obutton2 = UIButtons->CreateChildObj<BaseObject>();
	auto button2 = Obutton2->CreateChildComponent<ButtonComp>("button2");
	Obutton2->CreateChildComponent<dae::TextureComp>("Level2.png");
	buttonGroup->linkButton(button2)->setGroup(buttonGroup);
	Obutton2->T()->SetPosition(100, 0);
}
