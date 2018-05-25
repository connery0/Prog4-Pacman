#pragma once
#include "GoalCalculationScript.h"
#include "../InputComp.h"
#include "../BaseObject.h"

class PlayerControlledGoalScript: public goalScript
{

	virtual std::pair<float, float> CalculateGoalSync(BaseObject* Parent) override
	{
		if (!m_Initialized)
			Init(Parent);

		std::pair<float,float>goal{0.f,0.f};
		if (input->isDown(MoveLeft))
			goal.first -= 1;
		if (input->isDown(MoveRight))
			goal.first+= 1;
		if (input->isDown(MoveUp))
			goal.second -= 1;
		if (input->isDown(MoveDown))
			goal.second += 1;

		return goal;
	}

	void PlayerControlledGoalScript::Init(BaseObject* Parent)
	{
		if (input == nullptr)
		{
			if (Parent)
			{
				input = Parent->GetComponent<InputComp>();
				if (!input)
				{
					input = Parent->CreateChildComponent<InputComp>();
				}
			}
			else
			{
				return;
			}
		}

		input->addInput(MoveLeft, 'A');
		input->addInput(MoveRight, 'D');
		input->addInput(MoveUp, 'W');
		input->addInput(MoveDown, 'S');

		m_Initialized = true;
	}


protected:
	enum Actions
	{
		MoveLeft,MoveRight,MoveUp,MoveDown
	};


private:
	std::shared_ptr<InputComp> input=nullptr;
	bool m_Initialized=false;

};
