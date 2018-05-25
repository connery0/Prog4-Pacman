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
	auto newRunner = std::make_shared<MazeRunner>(level, std::make_shared<PlayerControlledGoalScript>(), 50.f);
	newRunner->m_DoesTileBlock[Wall] = false;
	pacman->AddComponent(newRunner);
	m_Runners.push_back(newRunner);
	pacman->CreateChildComponent<PacmanAnimation>();
	pacman->CreateChildComponent<PacmanLogicComp>(level,1);

	auto newGhost = AddNew<BaseObject>();
	newGhost->T()->SetPosition(GlobalMaster::GetInstance().m_Level_PrisonTiles[0]);
	newGhost->CreateChildComponent<dae::TextureColliderComp>("Ghost.png");

	auto ghostRunner = std::make_shared<MazeRunner>(level, std::make_shared<goalScript>(), 50.f, true);
	newGhost->AddComponent(ghostRunner); 
	m_Runners.push_back(ghostRunner);
	newGhost->CreateChildComponent<GhostLogicComp>(level);

	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//auto fpsObject = std::make_shared<BaseObject>();
	//fpsObject->AddComponent(std::make_shared<dae::FpsComp>(fpsFont));
	//fpsObject->Tset(50, 50, 0);
	//Add(fpsObject);

	auto Player1ScorePanel=AddNew<BaseObject>();
	Player1ScorePanel->CreateChildComponent<dae::TextureColliderComp>("ScorePanel.png",false);
	Player1ScorePanel->CreateChildComponent<dae::ScoreComp>("  Score : ", 1, fpsFont)->SetOffset(8.f,6.f);
	Player1ScorePanel->T()->SetPosition(5, dae::Renderer::WINDOW_HEIGHT- Player1ScorePanel->T()->GetSize().second - 5);
}
