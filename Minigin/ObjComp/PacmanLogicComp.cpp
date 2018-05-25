#include "MiniginPCH.h"
#include "PacmanLogicComp.h"
#include "LevelObject.h"

PacmanLogicComp::PacmanLogicComp(std::shared_ptr<LevelObject> maze, int playerId):m_Maze(maze),m_PlayerId(playerId)
{

}

void PacmanLogicComp::Update(float deltaTime)
{
	auto floorType = m_Maze->getTile(m_pParentObject->T()->GetPosition());
	(void)floorType,deltaTime;
}
