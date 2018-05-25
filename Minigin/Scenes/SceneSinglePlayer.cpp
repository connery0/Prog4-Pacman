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
	auto newRunner = std::make_shared<MazeRunner>(level, new PlayerControlledGoalScript(), 20.f);
	pacman->AddComponent(newRunner);
	m_Runners.push_back(newRunner);

	auto newGhost = AddNew<BaseObject>();
	newGhost->T()->SetPosition(GlobalMaster::GetInstance().m_Level_PrisonTiles[0]);
	newGhost->CreateChildComponent<dae::TextureColliderComp>("Ghost.png");

	goalScript tempGoalCalc{};
	auto ghostRunner = std::make_shared<MazeRunner>(level, new goalScript(), 20.f, true);
	newGhost->AddComponent(ghostRunner); 
	m_Runners.push_back(ghostRunner);

	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	auto fpsObject = std::make_shared<BaseObject>();
	fpsObject->AddComponent(std::make_shared<dae::FpsComp>(fpsFont));
	fpsObject->Tset(50, 50, 0);

	Add(fpsObject);
}
