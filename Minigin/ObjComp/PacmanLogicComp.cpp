#include "MiniginPCH.h"
#include "PacmanLogicComp.h"
#include "LevelObject.h"
#include "../GlobalGameMaster/GlobalMaster.h"
#include <random>
#include "TextureColliderComp.h"
#include "../Scenes/SceneManager.h"
#include "../Scenes/Scene.h"
#include "GhostLogicComp.h"

PacmanLogicComp::PacmanLogicComp(std::shared_ptr<LevelObject> maze, int playerId):m_Maze(maze),m_PlayerId(playerId)
{

}

void PacmanLogicComp::Update(float deltaTime)
{
	CheckFloor();

	if(m_PowerupTime>0)
	{
		m_PowerupTime-=deltaTime;
		if(m_PowerupTime<=0)
		{
			auto texture = m_pParentObject->GetComponent<dae::TextureColliderComp>(false);
			texture->ChangeTexture("Pacman.png");
		}
	}
	CheckCollision();
	if(isDead)
		Die();
}

void PacmanLogicComp::CheckFloor()
{
	auto floorType = m_Maze->getTile(m_pParentObject->T()->GetPosition());
	int addScore = 0;
	bool atePowerup = false;
	switch (floorType) {
	case Coin:
		addScore = 1;
		m_Maze->pickupTile(m_pParentObject->T()->GetPosition());
		break;
	case Powerup:
		atePowerup = true;
		m_Maze->pickupTile(m_pParentObject->T()->GetPosition());
		break;
	case Fruit:
		addScore = 50;
		m_Maze->pickupTile(m_pParentObject->T()->GetPosition());
		break;
	default:return;
	}


	if (addScore>0)
	{
		auto& gm = GlobalMaster::GetInstance();
		gm.m_PlayerScore[m_PlayerId] = gm.m_PlayerScore[m_PlayerId] + addScore;
	}
	if (atePowerup)
	{
		m_PowerupTime=maxPowerupTime;
		auto texture = m_pParentObject->GetComponent<dae::TextureColliderComp>(false);
		texture->ChangeTexture("PacmanBuff.png");		
	}
}

void PacmanLogicComp::CheckCollision()
{
	auto& sceneM = SceneManager::GetInstance();
	std::vector<std::shared_ptr<BaseObject>> runnerList = sceneM.GetActiveScene()->getObjectsWithComponent<MazeRunner>();
	if (runnerList.size()>1)
	{
		for (auto otherObj : runnerList)
		{
			if (m_pParentObject->CollidesWith(otherObj))
			{
				//see if you hit a ghost
				auto ghostLogic = otherObj->GetComponent<GhostLogicComp>();
				if (ghostLogic)
				{
					if (m_PowerupTime>0)
					{	//eat the ghost
						ghostLogic->isDead = true;
						continue;
					}
					else
					{
						isDead = true;
						return; //No point in checking further
					}
				}
			}
		}
	}
}

void PacmanLogicComp::Die()
{
	isDead=false;
	auto& gm= GlobalMaster::GetInstance();
	gm.m_PlayerDeaths[m_PlayerId]= gm.m_PlayerDeaths[m_PlayerId]+1;
	if(gm.m_PlayerDeaths[m_PlayerId]<gm.m_PlayerMaxDeaths)
	{
		if(gm.m_Level_SpawnPoints.size()>1)
			m_pParentObject->T()->SetPosition(gm.m_Level_SpawnPoints[m_PlayerId]);
		else
			m_pParentObject->T()->SetPosition(gm.m_Level_SpawnPoints[0]);
	}
	else
	{
		m_pParentObject->remove=true;
	}

}