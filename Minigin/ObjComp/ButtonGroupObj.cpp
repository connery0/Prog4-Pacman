#pragma once
#include "MiniginPCH.h"
#include "ButtonGroupObj.h"
#include "ButtonComp.h"

void ButtonGroupComp::ButtonClicked(std::string buttonGoal)
{
	for (auto button : buttonList)
	{
		if (button->GetGoal() == buttonGoal)
			button->setActive(true);
		else
			button->setActive(false);
	}
}

std::string ButtonGroupComp::getActive()
{
	for (auto button : buttonList)
	{
		if (button->isActive)
		{
			return button->GetGoal();
		}
	}
	return "";
}

void ButtonGroupComp::DisableAll()
{
	for (auto button : buttonList)
	{
		button->setActive(false);
	}
}

std::shared_ptr<ButtonComp> ButtonGroupComp::makeButton(std::string goal)
{
	auto button = m_pParentObject->CreateChildComponent<ButtonComp>(goal);
	linkButton(button);
	return button;
}

std::shared_ptr<ButtonComp> ButtonGroupComp::linkButton(std::shared_ptr<ButtonComp> buttonToAdd)
{
	buttonList.push_back(buttonToAdd);
	return buttonToAdd;
}
