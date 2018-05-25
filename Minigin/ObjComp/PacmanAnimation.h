#pragma once
#include "../MiniginPCH.h"

class PacmanAnimation:public BaseComponent
{
	void Update(float deltaTime) override;


protected:
	bool firstUpdate=true;
	std::pair<float,float> lastPos{-1.f,-1.f};
	std::pair<float, float> CurrentPos;
	enum faceDirection
	{
		RIGHT=0,DOWN=90,LEFT=180,UP=270
	};
};

inline void PacmanAnimation::Update(float deltaTime)
{
	(void)deltaTime;
	if(firstUpdate)
	{
		firstUpdate=false;
		CurrentPos=m_pParentObject->T()->GetPosition();
	}
	lastPos=CurrentPos;	
	CurrentPos = m_pParentObject->T()->GetPosition();

	std::pair<float, float> DeltaPos{CurrentPos.first-lastPos.first,CurrentPos.second- lastPos.second};

	//first >0 => right
	//second>0 => down
	
	//Find Biggest Change

	if (abs(DeltaPos.first)==abs(DeltaPos.second))
	{
		//If movement in both directions is the same, keep last movement
		//Most common ocurrence= standing still
		return;
	}
	else if(abs(DeltaPos.first)>abs(DeltaPos.second))
	{
		if(DeltaPos.first>0)
			m_pParentObject->T()->SetRotation(RIGHT);
		else
			m_pParentObject->T()->SetRotation(LEFT);
	}
	else if (abs(DeltaPos.first)<abs(DeltaPos.second))
	{
		if (DeltaPos.second>0)
			m_pParentObject->T()->SetRotation(DOWN);
		else
			m_pParentObject->T()->SetRotation(UP);
	}
}
