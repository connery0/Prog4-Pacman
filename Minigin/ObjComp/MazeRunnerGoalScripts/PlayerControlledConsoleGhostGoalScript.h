#pragma once
#include "../InputComp.h"
#include "PlayerControlledGhostGoalScript.h"

class PlayerControlledConsoleGhostGoalScript: public PlayerControlledGhostGoalScript
{
protected:
	void AddInputs() override
	{
		m_Input->addInput(MoveLeft, dae::ControllerButton::ButtonA);
		m_Input->addInput(MoveRight, dae::ControllerButton::ButtonX);
		m_Input->addInput(MoveUp, dae::ControllerButton::ButtonB);
		m_Input->addInput(MoveDown, dae::ControllerButton::ButtonY);
	}
};
