#pragma once
#include "GoalCalculationScript.h"
//#include "../InputComp.h"
#include "GhostGoalScript.h"
#include "../InputComp.h"

class PlayerControlledGhostGoalScript: public GhostGoalScript
{
	std::pair<float,float> CalculateRoamingGoal(BaseObject* Parent, float TimePassed) override
	{
		(void)TimePassed;

		if(!m_Initialized)
			Init(Parent);

		std::pair<float, float>goal{ 0.f,0.f };
		if (m_Input->isDown(MoveLeft))
			goal.first -= 1;
		if (m_Input->isDown(MoveRight))
			goal.first += 1;
		if (m_Input->isDown(MoveUp))
			goal.second -= 1;
		if (m_Input->isDown(MoveDown))
			goal.second += 1;

		return goal;
	}	
	void Init(BaseObject* Parent)
	{
		if (m_Input == nullptr)
		{
			if (Parent)
			{
				m_Input = Parent->GetComponent<InputComp>();
				if (!m_Input)
				{
					m_Input = Parent->CreateChildComponent<InputComp>();
				}
			}
			else
			{
				return;
			}
		}
		AddInputs();

		m_Initialized = true;
	}
protected:
	virtual void AddInputs()
	{
		m_Input->addInput(MoveLeft, 'A');
		m_Input->addInput(MoveRight, 'D');
		m_Input->addInput(MoveUp, 'W');
		m_Input->addInput(MoveDown, 'S');
	}
	enum Actions
	{
		MoveLeft, MoveRight, MoveUp, MoveDown
	};

	std::shared_ptr<InputComp> m_Input = nullptr;
	bool m_Initialized = false;

};
