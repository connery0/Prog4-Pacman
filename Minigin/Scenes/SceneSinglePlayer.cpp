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
	
	goalScript tempGoalCalc{};
	std::vector<TileType>blockers;
	blockers.push_back(TileType::Wall);
	pacman->AddComponent(std::make_shared<MazeRunner>(tempGoalCalc,1.0f,blockers));

	float counter = 2.0f;
	for (auto tileCenter: GlobalMaster::GetInstance().m_Level_PrisonTiles){
		auto newGhost = AddNew<BaseObject>();
		newGhost->T()->SetPosition(tileCenter);
		newGhost->CreateChildComponent<dae::TextureColliderComp>("Ghost.png");
		newGhost->AddComponent(std::make_shared<MazeRunner>(tempGoalCalc, counter, blockers)); counter++;
	}
}
