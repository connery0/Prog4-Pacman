#pragma once
#include "../InputComp.h"
#include "PlayerControlledGhostGoalScript.h"

class PlayerControlledKeyboard2GhostGoalScript: public PlayerControlledGhostGoalScript
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
