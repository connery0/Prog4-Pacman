#include "MiniginPCH.h"
#include "SceneTitleScreen.h"
#include "../ObjComp/LevelObject.h"
#include "../ObjComp/FpsComp.h"
#include "../ObjComp/TextureComp.h"
#include "../ObjComp/Player1MovementComp.h"
#include "../ObjComp/ButtonComp.h"
#include "../Core/Renderer.h"
#include "../GlobalGameMaster/GlobalMaster.h"
#include "SceneSinglePlayerMap2.h"
#include "SceneSinglePlayerMap1.h"


SceneTitleScreen::SceneTitleScreen(): Scene("TitleScene")
{
}


SceneTitleScreen::~SceneTitleScreen()
{

	if (LevelSelectGroup)LevelSelectGroup->Clear();
	if(Player1ControlGroup) Player1ControlGroup->Clear();
	if (Player2ControlGroup)Player2ControlGroup->Clear();
	if (ControllerOwnerGroup)ControllerOwnerGroup->Clear();
	if (Player2GameModeGroup)Player2GameModeGroup->Clear();
	if (StartGameGroup)StartGameGroup->Clear();
}

void SceneTitleScreen::Initialize()
{
	auto background = AddNew<BaseObject>();
	background->CreateChildComponent<dae::TextureComp>("background.jpg",false);

	auto title = AddNew<BaseObject>();
	title->CreateChildComponent<dae::TextureComp>("Title.png");
	title->T()->SetPosition(525.f,100.f);


	std::shared_ptr<BaseObject>TempObjectRef;
	std::shared_ptr<ButtonComp>TempButtonComponentRef;

	auto ButtonGroupManager = AddNew<BaseObject>();
	LevelSelectGroup = ButtonGroupManager->CreateChildComponent<ButtonGroupComp>();
	Player1ControlGroup = ButtonGroupManager->CreateChildComponent<ButtonGroupComp>();
	Player2ControlGroup = ButtonGroupManager->CreateChildComponent<ButtonGroupComp>();
	ControllerOwnerGroup = ButtonGroupManager->CreateChildComponent<ButtonGroupComp>();
	Player2GameModeGroup = ButtonGroupManager->CreateChildComponent<ButtonGroupComp>();
	StartGameGroup = ButtonGroupManager->CreateChildComponent<ButtonGroupComp>();

	auto LevelSelect = AddNew<BaseObject>();
	LevelSelect->CreateChildComponent<dae::TextureComp>("LevelTitle.png");
	LevelSelect->T()->SetPosition(300.f,200.f);
	TempObjectRef = LevelSelect->CreateChildObj<BaseObject>();
	TempObjectRef->T()->SetPosition(185,0);
	TempButtonComponentRef= TempObjectRef->CreateChildComponent<ButtonComp>("Level 1");
	LevelSelectGroup->linkButton(TempButtonComponentRef)->addGroup(LevelSelectGroup);
	TempObjectRef->CreateChildComponent<dae::TextureComp>("Level1.png");

	TempObjectRef = LevelSelect->CreateChildObj<BaseObject>();
	TempObjectRef->T()->SetPosition(390, 0);
	TempButtonComponentRef = TempObjectRef->CreateChildComponent<ButtonComp>("Level 2");
	LevelSelectGroup->linkButton(TempButtonComponentRef)->addGroup(LevelSelectGroup);
	TempObjectRef->CreateChildComponent<dae::TextureComp>("Level2.png");



	auto Player1Options=AddNew<BaseObject>();
	Player1Options->CreateChildComponent<dae::TextureComp>("P1.png");
	Player1Options->T()->SetPosition(100,300);
		//Keyboard
	TempObjectRef = Player1Options->CreateChildObj<BaseObject>();
	TempObjectRef->T()->SetPosition(60, 100);
	TempButtonComponentRef = TempObjectRef->CreateChildComponent<ButtonComp>("KeyboardP1");
	Player1ControlGroup->linkButton(TempButtonComponentRef)->addGroup(Player1ControlGroup);
	TempObjectRef->CreateChildComponent<dae::TextureComp>("Keyboard.png");
		//Controller
	TempObjectRef = Player1Options->CreateChildObj<BaseObject>();
	TempObjectRef->T()->SetPosition(60, 200);
	TempButtonComponentRef = TempObjectRef->CreateChildComponent<ButtonComp>("ControllerP1");
	ControllerOwnerGroup->linkButton(TempButtonComponentRef)->addGroup(ControllerOwnerGroup);
	Player1ControlGroup->linkButton(TempButtonComponentRef)->addGroup(Player1ControlGroup);
	TempObjectRef->CreateChildComponent<dae::TextureComp>("Controller.png");



		//Second Player
	auto Player2Options = AddNew<BaseObject>();
	Player2Options->CreateChildComponent<dae::TextureComp>("P2.png");
	Player2Options->T()->SetPosition(400, 300);
	
		//Not Joining
	TempObjectRef = Player2Options->CreateChildObj<BaseObject>();
	TempObjectRef->T()->SetPosition(60, 100);
	TempButtonComponentRef = TempObjectRef->CreateChildComponent<ButtonComp>("NoP2");
	Player2ControlGroup->linkButton(TempButtonComponentRef)->addGroup(Player2ControlGroup);
	Player2GameModeGroup->linkButton(TempButtonComponentRef)->addGroup(Player2GameModeGroup);
	TempObjectRef->CreateChildComponent<dae::TextureComp>("Disabled.png");
	
		//Keyboard
	TempObjectRef = Player2Options->CreateChildObj<BaseObject>();
	TempObjectRef->T()->SetPosition(60, 200);
	TempButtonComponentRef = TempObjectRef->CreateChildComponent<ButtonComp>("KeyboardP2");
	Player2ControlGroup->linkButton(TempButtonComponentRef)->addGroup(Player2ControlGroup);
	TempObjectRef->CreateChildComponent<dae::TextureComp>("Keyboard2.png");
		//Controller
	TempObjectRef = Player2Options->CreateChildObj<BaseObject>();
	TempObjectRef->T()->SetPosition(60, 300);
	TempButtonComponentRef = TempObjectRef->CreateChildComponent<ButtonComp>("ControllerP2");
	ControllerOwnerGroup->linkButton(TempButtonComponentRef)->addGroup(ControllerOwnerGroup);
	Player2ControlGroup->linkButton(TempButtonComponentRef)->addGroup(Player2ControlGroup);
	TempObjectRef->CreateChildComponent<dae::TextureComp>("Controller.png");

		//SecondPacman
	TempObjectRef = Player2Options->CreateChildObj<BaseObject>();
	TempObjectRef->T()->SetPosition(260, 100);
	TempButtonComponentRef = TempObjectRef->CreateChildComponent<ButtonComp>("Pacman");
	Player2GameModeGroup->linkButton(TempButtonComponentRef)->addGroup(Player2GameModeGroup);
	TempObjectRef->CreateChildComponent<dae::TextureComp>("Pacman.png");
	TempObjectRef->CreateChildComponent<dae::TextureComp>("Bow.png");

		//Ghost
	TempObjectRef = Player2Options->CreateChildObj<BaseObject>();
	TempObjectRef->T()->SetPosition(460, 100);
	TempButtonComponentRef = TempObjectRef->CreateChildComponent<ButtonComp>("Ghost");
	Player2GameModeGroup->linkButton(TempButtonComponentRef)->addGroup(Player2GameModeGroup);
	TempObjectRef->CreateChildComponent<dae::TextureComp>("Ghost2.png");
	TempObjectRef->CreateChildComponent<dae::TextureComp>("Eyes.png");


	//GO
	auto StartButton = AddNew<BaseObject>();
	TempButtonComponentRef=StartButton->CreateChildComponent<ButtonComp>("Start");
	StartGameGroup->linkButton(TempButtonComponentRef)->setGroup(StartGameGroup);
	StartButton->T()->SetPosition(520, 730);
	StartButton->CreateChildComponent<dae::TextureComp>("Start.png");
}

void SceneTitleScreen::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	if(StartGameGroup->getActive()=="Start")
	{
		if(CanStartCheck())
		{
			StartGameGroup->DisableAll();
			auto& gm = GlobalMaster::GetInstance();
			gm.resetVars();

			
			if(Player1ControlGroup->getActive()=="KeyboardP1")
				gm.player1UsesKeyboard=true;
			else
				gm.player1UsesKeyboard=false;


			if (Player2ControlGroup->getActive() == "KeyboardP2")
				gm.player2UsesKeyboard = true;
			else
				gm.player2UsesKeyboard = false;


			if (Player2GameModeGroup->getActive()=="NoP2")
				gm.player2Active = false;
			else if(Player2GameModeGroup->getActive()=="Pacman")
			{
				gm.player2Active = true;
				gm.player2IsPacman=true;
			}
			else
			{	gm.player2Active = true;
				gm.player2IsPacman=false;
			}

			auto& sceneM = SceneManager::GetInstance();
			if(LevelSelectGroup->getActive()=="Level 1")
			{
				sceneM.AddScene(std::make_shared<SceneSinglePlayerMap1>());
				//add level 1
			}else
			{
				sceneM.AddScene(std::make_shared<SceneSinglePlayerMap2>());
			}
		}		
		else
			StartGameGroup->DisableAll();	
	}
}

bool SceneTitleScreen::CanStartCheck()
{
	return (
			!(LevelSelectGroup->getActive() == "")
		 && !(Player1ControlGroup->getActive() == "")
		 && !(Player2ControlGroup->getActive() == "")
		 && !(Player2GameModeGroup->getActive() == "")
		 );
}
