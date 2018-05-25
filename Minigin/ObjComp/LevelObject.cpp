#include "MiniginPCH.h"
#include "LevelObject.h"
#include <fstream>
#include <sstream>
#include <string>
#include "../Core/ResourceManager.h"
#include "../Core/Renderer.h"
#include "../GlobalGameMaster/GlobalMaster.h"

LevelObject::LevelObject(std::string FileName):BaseObject()
{
	LoadLevel(FileName);
	t_Wall= dae::ResourceManager::GetInstance().LoadTexture(FileNameWall);
	t_Floor = dae::ResourceManager::GetInstance().LoadTexture(FileNameFloor);
	t_Prison = dae::ResourceManager::GetInstance().LoadTexture(FileNamePrison);
	t_Coin = dae::ResourceManager::GetInstance().LoadTexture(FileNameCoin);
	t_Powerup = dae::ResourceManager::GetInstance().LoadTexture(FileNamePowerup);
	t_Fruit= dae::ResourceManager::GetInstance().LoadTexture(FileNameFruit);
}

void LevelObject::Render() const
{
	auto& renderer = dae::Renderer::GetInstance();
	std::pair<float, float> Position {0.f,0.f};
	while (Position.second<m_Height)
	{
		Position.first=0;
		while (Position.first<m_Width)
		{
			size_t currentIndex = static_cast<size_t>(Position.first+ Position.second*m_Width);
			switch (m_Tiles[currentIndex]) { 
				case Wall:
					renderer.RenderTexture(*t_Wall, (0.5f+Position.first)*m_TileSize, (0.5f+Position.second)*m_TileSize, 0);
					break;
				case Floor:
					renderer.RenderTexture(*t_Floor, (0.5f+Position.first)*m_TileSize, (0.5f+Position.second)*m_TileSize, 0);
					break;
				case Prison:
					renderer.RenderTexture(*t_Prison, (0.5f+Position.first)*m_TileSize, (0.5f+Position.second)*m_TileSize, 0);
					break;
				case Coin:
					renderer.RenderTexture(*t_Floor, (0.5f+Position.first)*m_TileSize, (0.5f+Position.second)*m_TileSize, 0);
					renderer.RenderTexture(*t_Coin, (0.5f+Position.first)*m_TileSize, (0.5f+Position.second)*m_TileSize, 0);
					break;
				case Powerup:
					renderer.RenderTexture(*t_Floor, (0.5f+Position.first)*m_TileSize, (0.5f+Position.second)*m_TileSize, 0);
					renderer.RenderTexture(*t_Powerup, (0.5f+Position.first)*m_TileSize, (0.5f+Position.second)*m_TileSize, 0);
					break;
				case Fruit:
					renderer.RenderTexture(*t_Floor, (0.5f+Position.first)*m_TileSize, (0.5f+Position.second)*m_TileSize, 0);
					renderer.RenderTexture(*t_Fruit, (0.5f+Position.first)*m_TileSize, (0.5f+Position.second)*m_TileSize, 0);
					break;
			}
			Position.first++;
		}
		Position.second++;
	}
}

void LevelObject::LoadLevel()
{
	auto& gm = GlobalMaster::GetInstance();
	gm.m_Level_SpawnPoints.clear();
	gm.m_Level_PrisonTiles.clear();

	m_Tiles.clear();
	m_Tiles.resize(static_cast<size_t>(m_Width*m_Height));
	std::string delimiter = ",";

	size_t pos = 0;
	std::string token;
	std::ifstream infile(m_LevelString);
	std::string line;

	int vertical = 0;
	while (getline(infile, line)&&vertical<m_Height/*excel tends to add an extra line*/)
	{
		if(vertical==0)	/*first read*/
			line.erase(0, 3);//Remove Byte Order Mark sequence ( ﻿ )
		
		int horizontal = 0;
		while ((pos = line.find(delimiter)) != std::string::npos) {
			token = line.substr(0, pos);

			TileType nextTile=Wall;


			nextTile=static_cast<TileType>(token[0]);//No check here, don't mess up the level file
			if(nextTile==SpawnPoint)
			{
				std::pair<float, float> spawnPoint{ 
					static_cast<float>((0.5 + horizontal)*m_TileSize),
					static_cast<float>((0.5 + vertical)*m_TileSize)
				};
				gm.m_Level_SpawnPoints.push_back(spawnPoint);
				nextTile=Floor;
			}else if(nextTile==Prison)
			{
				std::pair<float, float> tileCenter{
					static_cast<float>((0.5+horizontal)*m_TileSize),
					static_cast<float>((0.5 + vertical)*m_TileSize)
				};
				gm.m_Level_PrisonTiles.push_back(tileCenter);
			}
				

			m_Tiles[static_cast<size_t>(horizontal+(vertical*m_Width))]=nextTile;
			
			line.erase(0, pos + delimiter.length());
			horizontal++;
		}
		++vertical;
	}
}


void LevelObject::LoadLevel(std::string FileName)
{
	m_LevelString=FileName;
	LoadLevel();
}

TileType LevelObject::getTile(float x, float y)
{
	return m_Tiles[static_cast<int>(x/m_TileSize)+ static_cast<int>(y / m_TileSize)*m_Width];
}

TileType LevelObject::pickupTile(float x, float y)
{
	const TileType returnValue = getTile(x,y);
	m_Tiles[static_cast<int>(x / m_TileSize) + static_cast<int>(y / m_TileSize)*m_Width]=Floor;
	return returnValue;
}

float LevelObject::getBorder(float p1, float p2)
{
//No data is lost, but a long chain of static casts would be more unreadable
#pragma warning(push)
#pragma warning (disable:4244)
	p1 = static_cast<int>(p1 / m_TileSize)*m_TileSize;
	p2 = static_cast<int>(p2 / m_TileSize)*m_TileSize;
#pragma warning(pop)

	if (p1>p2)return p1;
	return p2;

}