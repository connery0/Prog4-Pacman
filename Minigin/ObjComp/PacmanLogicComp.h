#pragma once
#include "BaseComponent.h"
#include "memory"

class LevelObject;

class PacmanLogicComp:public BaseComponent
{
public:
	PacmanLogicComp(std::shared_ptr<LevelObject>maze,int playerId);
	void Update(float deltaTime) override;
	void CheckFloor();
	void CheckCollision();

	void Die();
private:
	std::shared_ptr<LevelObject> m_Maze;
	int m_PlayerId;
	const float maxPowerupTime=10.f;
	float m_PowerupTime=0.f;
	bool isDead=false;
};
