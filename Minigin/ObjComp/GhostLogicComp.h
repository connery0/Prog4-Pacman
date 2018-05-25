#pragma once
#include "BaseComponent.h"
#include "memory"

class LevelObject;

class GhostLogicComp:public BaseComponent
{
public:
	GhostLogicComp(std::shared_ptr<LevelObject>maze);
	void Update(float deltaTime) override;
	//void CheckFloor();

	bool isDead=false;
private:
	std::shared_ptr<LevelObject> m_Maze;
	int m_PlayerId;
	const float maxPowerupTime=10.f;
	float m_PowerupTime=0.f;
};
