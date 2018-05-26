#include "MiniginPCH.h"
#include "SceneSinglePlayer.h"
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


SceneSinglePlayer::SceneSinglePlayer(): Scene("SinglePlayerMap")
{
	SceneSinglePlayer::Initialize();
	isInitialized=true;
}


SceneSinglePlayer::~SceneSinglePlayer()
{
}

void SceneSinglePlayer::Initialize()
{
	auto level = std::make_shared<LevelObject>("../Data/Map2.csv");
	Add(level);

	auto pacman = AddNew<BaseObject>();
	pacman->CreateChildComponent<dae::TextureColliderComp>("Pacman.png");
	pacman->T()->SetPosition(GlobalMaster::GetInstance().m_Level_SpawnPoints[0]);
	
	std::vector<TileType>blockers;
	blockers.push_back(TileType::Wall);
	auto newRunner = std::make_shared<MazeRunner>(level, std::make_shared<PlayerControlledGoalScript>(), 70.f);
	newRunner->m_DoesTileBlock[Prison]=true;
	pacman->AddComponent(newRunner);
	m_Runners.push_back(newRunner);
	pacman->CreateChildComponent<PacmanAnimation>();
	pacman->CreateChildComponent<PacmanLogicComp>(level,0);
	//pacman->CreateChildObj<BaseObject>()->CreateChildComponent<dae::TextureComp>("Bow.png");

	auto newGhost = AddNew<BaseObject>();
	newGhost->T()->SetPosition(GlobalMaster::GetInstance().m_Level_PrisonTiles[0]);
	newGhost->CreateChildComponent<dae::TextureColliderComp>("Ghost2.png");

	auto ghostRunner = std::make_shared<MazeRunner>(level, std::make_shared<GhostGoalScript>(), 70.f, false);
	newGhost->AddComponent(ghostRunner); 
	m_Runners.push_back(ghostRunner);
	newGhost->CreateChildComponent<GhostLogicComp>(level);
	newGhost->CreateChildObj<BaseObject>()->CreateChildComponent<dae::TextureComp>("Eyes.png");
	//newGhost->CreateChildObj<BaseObject>()->CreateChildComponent<dae::TextureComp>("Bow.png");

	auto newGhost2 = AddNew<BaseObject>();
	newGhost2->T()->SetPosition(GlobalMaster::GetInstance().m_Level_PrisonTiles[3]);
	newGhost2->CreateChildComponent<dae::TextureColliderComp>("Ghost2.png");

	auto ghostRunner2 = std::make_shared<MazeRunner>(level, std::make_shared<GhostGoalScript>(), 70.f, false);
	newGhost2->AddComponent(ghostRunner2);
	m_Runners.push_back(ghostRunner2);
	newGhost2->CreateChildComponent<GhostLogicComp>(level);
	newGhost2->CreateChildObj<BaseObject>()->CreateChildComponent<dae::TextureComp>("Eyes.png");
	newGhost2->CreateChildObj<BaseObject>()->CreateChildComponent<dae::TextureComp>("Bow.png");



	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//auto fpsObject = std::make_shared<BaseObject>();
	//fpsObject->AddComponent(std::make_shared<dae::FpsComp>(fpsFont));
	//fpsObject->Tset(50, 50, 0);
	//Add(fpsObject);

	auto Player1ScorePanel=AddNew<BaseObject>();
	Player1ScorePanel->CreateChildComponent<dae::TextureColliderComp>("ScorePanel.png",false);
	Player1ScorePanel->CreateChildComponent<dae::ScoreComp>("  Score : ",0, fpsFont)->SetOffset(8.f,6.f);
	Player1ScorePanel->T()->SetPosition(5, dae::Renderer::WINDOW_HEIGHT- Player1ScorePanel->T()->GetSize().second - 5);

	auto lifeIndicator = Player1ScorePanel->CreateChildObj<BaseObject>();
	lifeIndicator->T()->SetPosition(50.f,-25.f);
	auto lifeChild = lifeIndicator->CreateChildObj<BaseObject>();
	lifeChild->CreateChildComponent<LifeIndicator>(0,0);
	lifeChild->T()->SetPosition(0.f,0.f);
	
	lifeChild = lifeIndicator->CreateChildObj<BaseObject>();
	lifeChild->CreateChildComponent<LifeIndicator>(0, 1);
	lifeChild->T()->SetPosition(25.f, 0.f);

	lifeChild = lifeIndicator->CreateChildObj<BaseObject>();
	lifeChild->CreateChildComponent<LifeIndicator>(0, 2);
	lifeChild->T()->SetPosition(50.f, 0.f);
}
