#include "MiniginPCH.h"
#include "GhostLogicComp.h"
#include "LevelObject.h"
#include "../GlobalGameMaster/GlobalMaster.h"
#include <random>
#include "TextureColliderComp.h"
#include "../Scenes/SceneManager.h"
#include "../Scenes/Scene.h"

GhostLogicComp::GhostLogicComp(std::shared_ptr<LevelObject> maze):m_Maze(maze)
{

}

void GhostLogicComp::Update(float deltaTime)
{
	(void)deltaTime;
	if(isDead)
		m_pParentObject->remove=true;
}
