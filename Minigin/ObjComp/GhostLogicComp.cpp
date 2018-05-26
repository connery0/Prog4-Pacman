#include "MiniginPCH.h"
#include "GhostLogicComp.h"
#include "LevelObject.h"
#include "../GlobalGameMaster/GlobalMaster.h"
#include <random>
#include "TextureColliderComp.h"
#include "../Scenes/SceneManager.h"
#include "../Scenes/Scene.h"
#include <valarray>

GhostLogicComp::GhostLogicComp(std::shared_ptr<LevelObject> maze,float initialDelay):m_Maze(maze),isGhosting(true),m_RespawnTimer(initialDelay)
{
}

void GhostLogicComp::Update(float deltaTime)
{
	(void)deltaTime;
	if(isDead&&!isGhosting)
	{
		isGhosting = true;
		m_pParentObject->GetComponent<dae::TextureColliderComp>()->isActive=false;
		m_pParentObject->GetComponent<MazeRunner>()->m_DoesTileBlock[Wall] = false;
	}
	if(isDead&&isGhosting)
	{
		if(GetdistanceToStartPosRough()<RespawnRadius)
		{
			isDead=false;		
			m_pParentObject->GetComponent<dae::TextureColliderComp>()->isActive = true;
			m_pParentObject->GetComponent<MazeRunner>()->m_DoesTileBlock[Floor] = true;
			m_pParentObject->GetComponent<MazeRunner>()->m_DoesTileBlock[Coin] = true;
			m_pParentObject->GetComponent<MazeRunner>()->m_DoesTileBlock[Fruit] = true;
			m_pParentObject->GetComponent<MazeRunner>()->m_DoesTileBlock[Powerup] = true;
			m_pParentObject->GetComponent<MazeRunner>()->m_DoesTileBlock[Wall] = true;
			m_RespawnTimer=MaxRespawnTime;
		}
	}

	if(!isDead && isGhosting)
	{
		m_RespawnTimer-=deltaTime;
		if(m_RespawnTimer<=0)
		{
			isGhosting=false;
			m_pParentObject->GetComponent<MazeRunner>()->m_DoesTileBlock[Floor]=false;
			m_pParentObject->GetComponent<MazeRunner>()->m_DoesTileBlock[Coin] = false;
			m_pParentObject->GetComponent<MazeRunner>()->m_DoesTileBlock[Fruit] = false;
			m_pParentObject->GetComponent<MazeRunner>()->m_DoesTileBlock[Powerup] = false;
		}
	}		
}

float GhostLogicComp::GetdistanceToStartPosRough()
{
	auto pos = m_pParentObject->T()->GetPosition();
	return std::abs(m_StartPos.first- pos.first) + std::abs(m_StartPos.second - pos.second);
}
