#pragma once
#include "../MiniginPCH.h"
#include "TextureComp.h"
#include "../GlobalGameMaster/GlobalMaster.h"

class LifeIndicator:public dae::TextureComp
{
public:
	LifeIndicator(int playerId,int visibleTreshold):m_Id(playerId), m_Treshold(visibleTreshold), ALIVE("PacLive.png"),DEAD("PacDead.png"), TextureComp("PacLive.png"){};
	void Update(float deltaTime) override
	{
		(void)deltaTime;
		auto& gm = GlobalMaster::GetInstance();
		if(hasLivingTexture&&gm.m_PlayerDeaths[m_Id]>m_Treshold)
		{
			hasLivingTexture=false;
			ChangeTexture(DEAD);
		}else if(hasLivingTexture==false&&gm.m_PlayerDeaths[m_Id]<=m_Treshold)
		{
			hasLivingTexture = true;
			ChangeTexture(ALIVE);
		}
	};

protected:
	const int m_Id;
	const int m_Treshold;
	bool hasLivingTexture=true;
	const std::string ALIVE;
	const std::string DEAD;
};