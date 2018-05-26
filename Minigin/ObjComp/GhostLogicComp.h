#pragma once
#include "BaseComponent.h"
#include "memory"

class LevelObject;

class GhostLogicComp:public BaseComponent
{
public:
	GhostLogicComp(std::shared_ptr<LevelObject>maze,float initialDelay=0.f);
	void Update(float deltaTime) override;
	void addParent(BaseObject* parentObj) override
	{
		BaseComponent::addParent(parentObj);
		m_StartPos=parentObj->T()->GetPosition();
	};

	bool isDead=false;
	bool isGhosting=false;
	std::pair<float,float>m_StartPos;
	std::shared_ptr<LevelObject> m_Maze;

private:
	float GetdistanceToStartPosRough();

	int m_PlayerId;

	const float RespawnRadius = 2.5f;
	const float MaxRespawnTime = 10.f;
	float m_RespawnTimer=0;
	
};
