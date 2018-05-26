#include "MiniginPCH.h"
#include "MazeRunner.h"
#include "MazeRunnerGoalScripts/GoalCalculationScript.h"
#include "../Scenes/SceneManager.h"
#include "../Scenes/Scene.h"
#include "../Core/Renderer.h"


MazeRunner::MazeRunner(std::shared_ptr<LevelObject> maze, std::shared_ptr<goalScript> goalCalc, float speed, bool isAsync) :isAsync(isAsync), m_Maze(maze), calculationObject(goalCalc), m_Speed(speed)
{
}


void MazeRunner::CalculateGoal(float deltaTime)
{
	if (isAsync)
	{
		timeSinceLastGoal += deltaTime;
		if(timeSinceLastGoal>=goalUpdateDelay)
		{
			if (goalCalculation.joinable())
				goalCalculation.join();
			std::promise<std::pair<float, float>> promise;
			m_Future = promise.get_future();
			goalCalculation = std::thread(&goalScript::CalculateGoalAsync, &*calculationObject, std::ref(m_pParentObject), std::ref(timeSinceLastGoal), std::move(promise));
			timeSinceLastGoal = 0;
		}
	}
	else
	{
		m_Goal = calculationObject->CalculateGoalSync(m_pParentObject,deltaTime);
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
	float charXborderPos= m_pParentObject->T()->GetPosition().first+ (m_Goal.first* m_pParentObject->T()->GetSize().first/2.0f) + m_Goal.first*(deltaTime*m_Speed*m_SpeedMod);
	if(charXborderPos>dae::Renderer::WINDOW_WIDTH)
		newPos.first=0+ m_pParentObject->T()->GetSize().first / 5.f;
	else if(charXborderPos<0)
	{
		newPos.first = dae::Renderer::WINDOW_WIDTH - m_pParentObject->T()->GetSize().first / 5.f;
	}
	else if(m_DoesTileBlock[m_Maze->getTile(charXborderPos,pos.second)])
	{
		newPos.first=m_Maze->getBorder(pos.first,charXborderPos)- (m_Goal.first* m_pParentObject->T()->GetSize().first / 2.0f);
		
	}else
	{
		newPos.first+= m_Goal.first*(deltaTime*m_Speed*m_SpeedMod);
	}

	//Calculate y movement

	float charYborderPos = m_pParentObject->T()->GetPosition().second + (m_Goal.second* m_pParentObject->T()->GetSize().second / 2.0f) + m_Goal.second*(deltaTime*m_Speed*m_SpeedMod);
	if (charYborderPos>=dae::Renderer::WINDOW_HEIGHT)
		newPos.second = 0 + m_pParentObject->T()->GetSize().second / 5.f;
	else if (charYborderPos<=0)
	{
		newPos.second = dae::Renderer::WINDOW_HEIGHT - m_pParentObject->T()->GetSize().second / 5.f;
	}
	else if (m_DoesTileBlock[m_Maze->getTile(pos.first, charYborderPos)])
	{
		newPos.second = m_Maze->getBorder(pos.second, charYborderPos)- (m_Goal.second* m_pParentObject->T()->GetSize().second / 2.0f);
	}
	else
	{
		newPos.second += m_Goal.second*(deltaTime*m_Speed*m_SpeedMod);
	}

	m_pParentObject->T()->SetPosition(newPos);
	
}

