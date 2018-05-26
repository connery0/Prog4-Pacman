#pragma once
#include "../Core/Singleton.h"

#include <vector>
#include <map>

class GlobalMaster : public dae::Singleton<GlobalMaster>
{
public:
	//Game Settings
	bool player1UsesKeyboard=true;
	bool player2UsesKeyboard=true;

	bool player2Active=false;
	bool player2IsPacman=true;

	//Map info - gets added when scene switches to a level
	std::vector<std::pair<float, float>> m_Level_SpawnPoints;
	std::vector<std::pair<float, float>> m_Level_PrisonTiles; //Locations for ghosts to return to/spawn on

	//Player scores, <playerId,Score>
	std::map<int,int>m_PlayerScore;
	//Player lives
	std::map<int, int>m_PlayerDeaths;
	int m_PlayerMaxDeaths=3;

	void resetVars()
	{
		for (auto const& element : m_PlayerScore)
		{
			m_PlayerScore[element.first]=0;
		}
		for (auto const& element : m_PlayerDeaths)
		{
			m_PlayerDeaths[element.first] = 0;
		}
		m_Level_SpawnPoints.clear();
		m_Level_PrisonTiles.clear();
	};

};

