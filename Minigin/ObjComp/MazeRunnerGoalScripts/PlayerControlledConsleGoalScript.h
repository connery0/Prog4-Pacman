#pragma once
#include "PlayerControlledGoalScript.h"
#include "PlayerControlledConsoleGhostGoalScript.h"

class PlayerControlledConsoleGoalScript: public PlayerControlledGoalScript
{

protected:
	void AddInputs() override
	{
		m_Input->addInput(MoveLeft, dae::ControllerButton::Left);
		m_Input->addInput(MoveRight, dae::ControllerButton::Right);
		m_Input->addInput(MoveUp, dae::ControllerButton::Up);
		m_Input->addInput(MoveDown, dae::ControllerButton::Down);
	}

};
