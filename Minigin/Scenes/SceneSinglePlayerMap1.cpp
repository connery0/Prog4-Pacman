#include "MiniginPCH.h"
#include "SceneSinglePlayerMap1.h"
#include "../ObjComp/LevelObject.h"
#include "../ObjComp/FpsComp.h"
#include "../ObjComp/TextureComp.h"
#include "../ObjComp/Player1MovementComp.h"
#include "../GlobalGameMaster/GlobalMaster.h"
#include "../ObjComp/TextureColliderComp.h"
#include "../ObjComp/MazeRunnerGoalScripts/GoalCalculationScript.h"
#include "../ObjComp/MazeRunner.h"
#include "../ObjComp/MazeRunnerGoalScripts/PlayerControlledGoalScript.h"
#include "../ObjComp/PacmanAnimation.h"
#include "../ObjComp/ScoreComp.h"
#include "../Core/Renderer.h"
#include "../ObjComp/PacmanLogicComp.h"
#include "../ObjComp/GhostLogicComp.h"
#include "../ObjComp/MazeRunnerGoalScripts/PlayerControlledKeyboardGoalScript.h"
#include "../ObjComp/MazeRunnerGoalScripts/GhostGoalScript.h"
#include "../ObjComp/MazeRunnerGoalScripts/PlayerControlledGhostGoalScript.h"
#include "../ObjComp/LifeIndicator.h"
#include "../ObjComp/MazeRunnerGoalScripts/PlayerControlledConsoleGhostGoalScript.h"
#include "../ObjComp/MazeRunnerGoalScripts/PlayerControlledKeyboardGhostGoalScript.h"
#include "../ObjComp/ButtonGroupObj.h"
#include "../ObjComp/ButtonComp.h"
#include "../ObjComp/MazeRunnerGoalScripts/PlayerControlledConsleGoalScript.h"


SceneSinglePlayerMap1::SceneSinglePlayerMap1(): Scene("SinglePlayerMap1")
{
	SceneSinglePlayerMap1::Initialize();
	isInitialized=true;
}


SceneSinglePlayerMap1::~SceneSinglePlayerMap1()
{
	backButton->Clear();
	dae::InputManager::GetInstance().Destroy();
}

void SceneSinglePlayerMap1::Initialize()
{

	auto level = std::make_shared<LevelObject>("../Data/Map1.csv");
	Add(level);


	///////////////////////
	//Player1
	///////////////////////
	auto pacman = AddNew<BaseObject>();
	pacman->CreateChildComponent<dae::TextureColliderComp>("Pacman.png");
	pacman->T()->SetPosition(GlobalMaster::GetInstance().m_Level_SpawnPoints[0]);

	std::shared_ptr<MazeRunner> newRunner;
	if (GlobalMaster::GetInstance().player1UsesKeyboard)
		newRunner = std::make_shared<MazeRunner>(level, std::make_shared<PlayerControlledGoalScript>(), 70.f);
	else
		newRunner = std::make_shared<MazeRunner>(level, std::make_shared<PlayerControlledConsoleGoalScript>(), 70.f);

	newRunner->m_DoesTileBlock[Prison] = true;
	pacman->AddComponent(newRunner);
	m_Runners.push_back(newRunner);
	pacman->CreateChildComponent<PacmanAnimation>();
	pacman->CreateChildComponent<PacmanLogicComp>(level, 0);
	//pacman->CreateChildObj<BaseObject>()->CreateChildComponent<dae::TextureComp>("Bow.png");

	///////////////////////
	//Player2
	///////////////////////
	if (GlobalMaster::GetInstance().player2Active && GlobalMaster::GetInstance().player2IsPacman)
	{
		auto pacmanP2 = AddNew<BaseObject>();
		pacmanP2->CreateChildComponent<dae::TextureColliderComp>("Pacman.png");
		pacmanP2->T()->SetPosition(GlobalMaster::GetInstance().m_Level_SpawnPoints[1]);

		std::shared_ptr<MazeRunner> player2Runner;
		if (GlobalMaster::GetInstance().player2UsesKeyboard)
			player2Runner = std::make_shared<MazeRunner>(level, std::make_shared<PlayerControlledKeyboard2GoalScript>(), 70.f);
		else
			player2Runner = std::make_shared<MazeRunner>(level, std::make_shared<PlayerControlledConsoleGoalScript>(), 70.f);

		player2Runner->m_DoesTileBlock[Prison] = true;
		pacmanP2->AddComponent(player2Runner);
		m_Runners.push_back(player2Runner);
		pacmanP2->CreateChildComponent<PacmanAnimation>();
		pacmanP2->CreateChildComponent<PacmanLogicComp>(level, 1);
		pacmanP2->CreateChildObj<BaseObject>()->CreateChildComponent<dae::TextureComp>("Bow.png");
	}


	bool firstGhostIsPlayerControlled = (GlobalMaster::GetInstance().player2Active) && (!GlobalMaster::GetInstance().player2IsPacman);
	{
		auto newGhost = AddNew<BaseObject>();
		newGhost->T()->SetPosition(GlobalMaster::GetInstance().m_Level_PrisonTiles[6]);
		newGhost->T()->AddTransform(0, 5, 0);//Bad starting position for ai, so slight offset
		newGhost->CreateChildComponent<dae::TextureColliderComp>("Ghost2.png");

		std::shared_ptr<MazeRunner> ghostRunner;
		if (firstGhostIsPlayerControlled)
		{
			if (GlobalMaster::GetInstance().player2UsesKeyboard)
				ghostRunner = std::make_shared<MazeRunner>(level, std::make_shared<PlayerControlledKeyboard2GhostGoalScript>(), 70.f);
			else
				ghostRunner = std::make_shared<MazeRunner>(level, std::make_shared<PlayerControlledConsoleGhostGoalScript>(), 70.f);
		}
		else
		{
			ghostRunner = std::make_shared<MazeRunner>(level, std::make_shared<GhostGoalScript>(), 70.f, false);
		}
		newGhost->AddComponent(ghostRunner);
		m_Runners.push_back(ghostRunner);
		newGhost->CreateChildComponent<GhostLogicComp>(level);
		newGhost->CreateChildObj<BaseObject>()->CreateChildComponent<dae::TextureComp>("Eyes.png");
		if (firstGhostIsPlayerControlled)
			newGhost->CreateChildObj<BaseObject>()->CreateChildComponent<dae::TextureComp>("Bow.png");
	}

	//semi prefabs!
	//addGhost(0, "Ghost.png",level);
	//addGhost(1, "Ghost3.png", level);
	//addGhost(3, "Ghost4.png", level);

	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	////////////////
	//UI
	////////////////
	{
		auto PlayerScorePanel = AddNew<BaseObject>();
		PlayerScorePanel->CreateChildComponent<dae::TextureColliderComp>("ScorePanel.png", false);
		PlayerScorePanel->CreateChildComponent<dae::ScoreComp>("  Score : ", 0, fpsFont)->SetOffset(8.f, 6.f);
		PlayerScorePanel->T()->SetPosition(5, dae::Renderer::WINDOW_HEIGHT - PlayerScorePanel->T()->GetSize().second - 5);

		auto lifeIndicator = PlayerScorePanel->CreateChildObj<BaseObject>();
		lifeIndicator->T()->SetPosition(50.f, -25.f);
		auto lifeChild = lifeIndicator->CreateChildObj<BaseObject>();
		lifeChild->CreateChildComponent<LifeIndicator>(0, 0);
		lifeChild->T()->SetPosition(0.f, 0.f);

		lifeChild = lifeIndicator->CreateChildObj<BaseObject>();
		lifeChild->CreateChildComponent<LifeIndicator>(0, 1);
		lifeChild->T()->SetPosition(25.f, 0.f);

		lifeChild = lifeIndicator->CreateChildObj<BaseObject>();
		lifeChild->CreateChildComponent<LifeIndicator>(0, 2);
		lifeChild->T()->SetPosition(50.f, 0.f);
	}
	//Player 2 - If ms. pacman
	if (GlobalMaster::GetInstance().player2Active && GlobalMaster::GetInstance().player2IsPacman)
	{
		auto PlayerScorePanel = AddNew<BaseObject>();
		PlayerScorePanel->CreateChildComponent<dae::TextureColliderComp>("ScorePanel.png", false);
		PlayerScorePanel->CreateChildComponent<dae::ScoreComp>("  Score : ", 1, fpsFont)->SetOffset(8.f, 6.f);
		PlayerScorePanel->T()->SetPosition(dae::Renderer::WINDOW_WIDTH - PlayerScorePanel->T()->GetSize().first - 5, dae::Renderer::WINDOW_HEIGHT - PlayerScorePanel->T()->GetSize().second - 5);
		PlayerScorePanel->CreateChildComponent<dae::TextureComp>("Bow.png", false);

		auto lifeIndicator = PlayerScorePanel->CreateChildObj<BaseObject>();
		lifeIndicator->T()->SetPosition(50.f, -25.f);
		auto lifeChild = lifeIndicator->CreateChildObj<BaseObject>();
		lifeChild->CreateChildComponent<LifeIndicator>(1, 0);
		lifeChild->T()->SetPosition(0.f, 0.f);

		lifeChild = lifeIndicator->CreateChildObj<BaseObject>();
		lifeChild->CreateChildComponent<LifeIndicator>(1, 1);
		lifeChild->T()->SetPosition(25.f, 0.f);

		lifeChild = lifeIndicator->CreateChildObj<BaseObject>();
		lifeChild->CreateChildComponent<LifeIndicator>(1, 2);
		lifeChild->T()->SetPosition(50.f, 0.f);
	}

	auto buttonObject = AddNew<BaseObject>();
	backButton = buttonObject->CreateChildComponent<ButtonGroupComp>();
	auto buttonC = buttonObject->CreateChildComponent<ButtonComp>("BACK");
	backButton->linkButton(buttonC)->setGroup(backButton);
	buttonObject->CreateChildComponent<dae::TextureComp>("Back.png", false);
}


void SceneSinglePlayerMap1::addGhost(int prisonTile,std::string texture,std::shared_ptr<LevelObject>level)
{
	//Extra Ghosts (always ai)
	{
		auto newGhost = AddNew<BaseObject>();
		newGhost->T()->SetPosition(GlobalMaster::GetInstance().m_Level_PrisonTiles[prisonTile]);
		newGhost->CreateChildComponent<dae::TextureColliderComp>(texture);

		auto ghostRunner2 = std::make_shared<MazeRunner>(level, std::make_shared<GhostGoalScript>(), 70.f, false);
		newGhost->AddComponent(ghostRunner2);
		m_Runners.push_back(ghostRunner2);
		newGhost->CreateChildComponent<GhostLogicComp>(level);
		newGhost->CreateChildObj<BaseObject>()->CreateChildComponent<dae::TextureComp>("Eyes.png");
	}
	
}

void SceneSinglePlayerMap1::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	if(backButton->getActive()=="BACK")
	{
		backButton->DisableAll();
		SceneManager::GetInstance().RemoveActiveScene("TitleScene");
	}
}
