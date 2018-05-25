#pragma once
#include "../Core/Singleton.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

class GlobalMaster : public dae::Singleton<GlobalMaster>
{
public:


	//Map info - gets added when scene switches to a level
	std::vector<std::pair<float, float>> m_Level_SpawnPoints;
	std::vector<std::pair<float, float>> m_Level_PrisonTiles; //Locations for ghosts to return to/spawn on

};

