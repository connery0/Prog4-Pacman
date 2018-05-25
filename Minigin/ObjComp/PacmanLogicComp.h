#pragma once
#include "BaseComponent.h"
#include "memory"

class LevelObject;

class PacmanLogicComp:public BaseComponent
{
public:
	PacmanLogicComp(std::shared_ptr<LevelObject>maze,int playerId);
	void Update(float deltaTime) override;

private:
	std::shared_ptr<LevelObject> m_Maze;
	int m_PlayerId;
};
