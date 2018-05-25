#include "MiniginPCH.h"
#include "MazeRunner.h"
#include "MazeRunnerGoalScripts/GoalCalculationScript.h"
#include "../Scenes/SceneManager.h"
#include "../Scenes/Scene.h"



MazeRunner::MazeRunner(std::shared_ptr<LevelObject> maze, goalScript* goalCalc, float speed, bool isAsync) :isAsync(isAsync), m_Maze(maze), calculationObject(goalCalc), m_Speed(speed)
{
}


void MazeRunner::CalculateGoal(float deltaTime)
{
	if (isAsync)
	{
		timeSinceLastGoal += deltaTime;
		if(timeSinceLastGoal>=goalUpdateDelay)
		{
			timeSinceLastGoal-=goalUpdateDelay;
			if (goalCalculation.joinable())
				goalCalculation.join();
			std::promise<std::pair<float, float>> promise;
			m_Future = promise.get_future();
			goalCalculation = std::thread(&goalScript::CalculateGoalAsync, &*calculationObject, std::ref(m_pParentObject), std::move(promise));
		}
	}
	else
	{
		m_Goal = calculationObject->CalculateGoalSync(m_pParentObject);
	}
}

void MazeRunner::Update(float deltaTime)
{
	(void)deltaTime;
	if(isAsync&&goalCalculation.joinable())
	{
			goalCalculation.join();
			m_Goal = m_Future.get();
	}

	std::pair<float, float> pos = m_pParentObject->T()->GetPosition();
		
	std::pair<float, float> newPos = pos;

	//todo: also check for collision if you arn't moving on an axis (not done now because 0 as movement ignores the border check
	//Calculate x movement
	float charXborderPos= m_pParentObject->T()->GetPosition().first+ (m_Goal.first* m_pParentObject->T()->GetSize().first/2.0f) + m_Goal.first*(deltaTime*m_Speed);
	if(m_DoesTileBlock[m_Maze->getTile(charXborderPos,pos.second)])
	{
		newPos.first=m_Maze->getBorder(pos.first,charXborderPos)- (m_Goal.first* m_pParentObject->T()->GetSize().first / 2.0f);
	}else
	{
		newPos.first+= m_Goal.first*(deltaTime*m_Speed);
	}

	//Calculate y movement
	float charYborderPos = m_pParentObject->T()->GetPosition().second + (m_Goal.second* m_pParentObject->T()->GetSize().second / 2.0f) + m_Goal.second*(deltaTime*m_Speed);
	if (m_DoesTileBlock[m_Maze->getTile(pos.first, charYborderPos)])
	{
		newPos.second = m_Maze->getBorder(pos.second, charYborderPos)- (m_Goal.second* m_pParentObject->T()->GetSize().second / 2.0f);
	}
	else
	{
		newPos.second += m_Goal.second*(deltaTime*m_Speed);
	}

	m_pParentObject->T()->SetPosition(newPos);
	
}

