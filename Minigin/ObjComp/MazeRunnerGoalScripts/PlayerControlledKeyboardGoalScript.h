#pragma once
#include "PlayerControlledGoalScript.h"

class PlayerControlledKeyboard2GoalScript: public PlayerControlledGoalScript
{

protected:
	void AddInputs() override
	{
		m_Input->addInput(MoveLeft, 'J');
		m_Input->addInput(MoveRight, 'L');
		m_Input->addInput(MoveUp, 'I');
		m_Input->addInput(MoveDown, 'K');		
	}

};
