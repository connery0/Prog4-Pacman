#pragma once
#include "TextureColliderComp.h"

class ButtonGroupComp;

class ButtonComp:public dae::TextureColliderComp
{
public:
	ButtonComp(std::string goal):m_goal(goal),isActive(false), ACTIVE("ButtonOn.png"),INACTIVE("ButtonOff.png"),TextureColliderComp("ButtonOff.png")
	{};
	~ButtonComp()
	{
		ButtonGroups.clear();
	}
	void setGroup(std::shared_ptr<ButtonGroupComp>newGroup);
	void addGroup(std::shared_ptr<ButtonGroupComp>newGroup);

	std::string GetGoal();
	void click(int x, int y);
	void setActive(bool state);

	bool isActive;
private:
	std::vector<std::shared_ptr<ButtonGroupComp>>ButtonGroups;
	std::string m_goal;
	const std::string ACTIVE;
	const std::string INACTIVE;
};