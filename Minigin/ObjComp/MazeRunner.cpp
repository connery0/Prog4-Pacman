#include "MiniginPCH.h"
#include "MazeRunner.h"
#include "MazeRunnerGoalScripts/GoalCalculationScript.h"
#include "../Scenes/SceneManager.h"
#include "../Scenes/Scene.h"

MazeRunner::MazeRunner(goalScript& goalCalc, const float speed, const std::vector<TileType> blockingTiles): calculationObject(goalCalc),m_Speed(speed),m_blockingTiles(blockingTiles)
{
	m_Maze=SceneManager::GetInstance().GetActiveScene()->getChild<LevelObject>();
}

void MazeRunner::CalculateGoal()
{
	std::promise<glm::vec2> promise;
	auto future = promise.get_future();
	m_Future=std::move(future);
	goalCalculation = std::thread(&goalScript::CalculateGoal, &calculationObject, std::ref(m_pParentObject),std::move(promise));

	hasThread=true;
}

void MazeRunner::Update(float deltaTime)
{
	(void)deltaTime;
	if(hasThread&&m_Maze!=nullptr)
	{
		goalCalculation.join();
		glm::vec2 goalDirection = m_Future.get();		
		int a = 5;
		(void)a;
		
	}
}

