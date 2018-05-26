#pragma once
#include "GoalCalculationScript.h"
//#include "../InputComp.h"
#include "../BaseObject.h"
#include "../GhostLogicComp.h"
#include <map>

class GhostGoalScript: public goalScript
{
public:
	GhostGoalScript()
	{
		//Diferent personalities
		float xPatienceMod = rand()%static_cast<int>(xPatienceMax) - (xPatienceMax/2.f);
		xPatienceMax+=xPatienceMod;

		float yPatienceMod = rand() % static_cast<int>(yPatienceMax) - (yPatienceMax / 2.f);
		yPatienceMax+=yPatienceMod;
	}

	virtual std::pair<float, float> CalculateGoalSync(BaseObject* Parent, float TimePassed) override
	{
		if(m_Logic==nullptr)
		{
			m_Logic=Parent->GetComponent<GhostLogicComp>();
		}
		if(m_Logic!=nullptr)
		{
			if(m_Logic->isDead)
			{
				return CalculateStartPosGoal(Parent);
			}
			return  CalculateRoamingGoal(Parent, TimePassed);

		}
		return std::make_pair(0.f,0.f);
	}

	std::pair<float,float> CalculateStartPosGoal(BaseObject* Parent)
	{
		float xGoal=0.f;
		if (Parent->T()->GetPosition().first > m_Logic->m_StartPos.first)
		{
			xGoal=-1.f;
		}
		else if(Parent->T()->GetPosition().first < m_Logic->m_StartPos.first)
		{
			xGoal=+1.f;
		}

		float yGoal = 0.f;
		if (Parent->T()->GetPosition().second > m_Logic->m_StartPos.second)
		{
			yGoal = -1.f;
		}
		else if (Parent->T()->GetPosition().second < m_Logic->m_StartPos.second)
		{
			yGoal = +1.f;
		}

		return std::make_pair(xGoal,yGoal);
	}

	virtual std::pair<float,float> CalculateRoamingGoal(BaseObject* Parent, float TimePassed)
	{
		if (m_Logic->isGhosting)//Player can move around at this point, ai stays frozen in place
			return  std::make_pair(0.f, 0.f);

		if(m_Target==nullptr)
		{
			auto& sceneM = SceneManager::GetInstance();
			auto runners = sceneM.GetActiveScene()->getObjectsWithComponent<MazeRunner>();
			for (auto object:runners)
			{
				m_TargetLogic= object->GetComponent<PacmanLogicComp>();
				if(m_TargetLogic!=nullptr){
					m_Target=object;
					break;
				}
			}
			lastPosition = LevelObject::GetTileCoord(Parent->T()->GetPosition());
		}
		if (m_Target != nullptr)
		{
			std::pair<float,float>toPlayerDirection = std::make_pair(
				cap(m_Target->T()->GetPosition().first + playerTargetMod.first - Parent->T()->GetPosition().first),
				cap(m_Target->T()->GetPosition().second + playerTargetMod.second - Parent->T()->GetPosition().second)
			);
			std::pair<int,int> currentPos= LevelObject::GetTileCoord(Parent->T()->GetPosition());

			//When stuck on x, try to move in y direction
			if(lostXpatience)
			{
				if(currentPos.first == lastPosition.first)//Still stuck on same X pos
				{
					toPlayerDirection.second*=-1;//Change Y direction to try and move away from the wall blocking you					
					xPatience-=TimePassed/2.f;
					if(xPatience<=0)
					{
						lostXpatience = false;
						xPatience = 0;
					}
				}else
				{
					lostXpatience=false;
					xPatience=0;
				}
			}else
			{
				if (currentPos.first == lastPosition.first)//Still stuck on same X pos
				{
					xPatience+=TimePassed;
					if(xPatience>=xPatienceMax)
					{ 
						lostXpatience=true;
					}
				}				
			}

			//When stuck on y, try to move in x direction
			if (lostYpatience)
			{
				if (currentPos.second == lastPosition.second)//Still stuck on same X pos
				{
					if(toPlayerDirection.first==0)
					{
					}
					else
						toPlayerDirection.first *= -1;//Change Y direction to try and move away from the wall blocking 

					yPatience -= TimePassed / 2.f;
					if (yPatience <= 0)
					{
						lostYpatience = false;
						yPatience = 0;
					}
				}
				else
				{
					lostYpatience = false;
					yPatience = 0;
				}
			}
			else
			{
				if (currentPos.second == lastPosition.second)//Still stuck on same X pos
				{
					yPatience += TimePassed;
					if (yPatience >= yPatienceMax)
					{
						lostYpatience = true;
					}
				}
			}


			if(m_TargetLogic->isPowered())
			{
				toPlayerDirection.first *= -1;
				toPlayerDirection.second*= -1;
			}

			
			lastPosition = currentPos;
			return toPlayerDirection;
		}
		return  std::make_pair(1.f, 1.f);
	}
	

	std::shared_ptr<GhostLogicComp>m_Logic;
	
protected:
	float cap(float value)
	{
		if(value>=1.f)return 1.f;
		if (value <= -1.f)return -1.f;
		return 0.f;
	}

	std::shared_ptr<BaseObject> m_Target;
	std::shared_ptr<PacmanLogicComp> m_TargetLogic;
	std::pair<float,float> playerTargetMod{0.f,0.f};
	
	std::pair<int,int> lastPosition;

	float xPatience = 0.f;
	float xPatienceMax = 10.f;
	bool lostXpatience=false;
	
	float yPatience = 0.f;
	float yPatienceMax = 10.f;
	bool lostYpatience = false;
};
