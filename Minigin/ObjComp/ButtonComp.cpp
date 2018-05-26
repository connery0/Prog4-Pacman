#include "MiniginPCH.h"
#include "ButtonComp.h"
#include "BaseComponent.h"
#include "ButtonGroupObj.h"
#include "TextureColliderComp.h"


void ButtonComp::setGroup(std::shared_ptr<ButtonGroupComp> newGroup){ButtonGroups.clear();ButtonGroups.push_back(newGroup);}

void ButtonComp::addGroup(std::shared_ptr<ButtonGroupComp> newGroup) { ButtonGroups.push_back(newGroup); }

std::string ButtonComp::GetGoal()
{
	return m_goal;
}

void ButtonComp::click(int x, int y)
{
	if (m_pParentObject->CollidesWithPoint(x, y))
		for (auto group : ButtonGroups)
			group->ButtonClicked(m_goal);
}

void ButtonComp::setActive(bool state)
{
	if (state == isActive) return;

	isActive = state;
	if (isActive)
		ChangeTexture(ACTIVE);
	else
		ChangeTexture(INACTIVE);
}
