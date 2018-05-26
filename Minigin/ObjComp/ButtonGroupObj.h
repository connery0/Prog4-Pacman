#pragma once
#include "../MiniginPCH.h"

class ButtonComp;

class ButtonGroupComp:public BaseComponent
{
public:

	std::shared_ptr<ButtonComp> makeButton(std::string goal);
	std::shared_ptr<ButtonComp> linkButton(std::shared_ptr<ButtonComp> buttonToAdd);

	void ButtonClicked(std::string buttonGoal);

	std::string getActive();
	void DisableAll();
	void Clear()
	{
		buttonList.clear();
	}
protected:
	std::vector<std::shared_ptr<ButtonComp>> buttonList;
};