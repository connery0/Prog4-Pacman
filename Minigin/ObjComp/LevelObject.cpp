#include "MiniginPCH.h"
#include "LevelObject.h"
#include <fstream>
#include <sstream>
#include <string>
#include "../Core/ResourceManager.h"
#include "../Core/Renderer.h"

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
	glm::vec2 Position {0,0};
	while (Position.y<m_Height)
	{
		Position.x=0;
		while (Position.x<m_Width)
		{
			size_t currentIndex = static_cast<size_t>(Position.x+ Position.y*m_Width);
			switch (m_Tiles[currentIndex]) { 
				case Wall:
					renderer.RenderTexture(*t_Wall, Position.x*m_TileSize, Position.y*m_TileSize, 0);
					break;
				case Floor:
					renderer.RenderTexture(*t_Floor, Position.x*m_TileSize, Position.y*m_TileSize, 0);
					break;
				case Prison:
					renderer.RenderTexture(*t_Prison, Position.x*m_TileSize, Position.y*m_TileSize, 0);
					break;
				case Coin:
					renderer.RenderTexture(*t_Floor, Position.x*m_TileSize, Position.y*m_TileSize, 0);
					renderer.RenderTexture(*t_Coin, Position.x*m_TileSize, Position.y*m_TileSize, 0);
					break;
				case Powerup:
					renderer.RenderTexture(*t_Floor, Position.x*m_TileSize, Position.y*m_TileSize, 0);
					renderer.RenderTexture(*t_Powerup, Position.x*m_TileSize, Position.y*m_TileSize, 0);
					break;
				case Fruit:
					renderer.RenderTexture(*t_Floor, Position.x*m_TileSize, Position.y*m_TileSize, 0);
					renderer.RenderTexture(*t_Fruit, Position.x*m_TileSize, Position.y*m_TileSize, 0);
					break;
			}

			renderer.RenderTexture(*dae::ResourceManager::GetInstance().LoadTexture("Pacman.png") , m_SpawnPoint.x*m_TileSize, m_SpawnPoint.y*m_TileSize, 0);
			



			Position.x++;
		}
		Position.y++;
	}
}

void LevelObject::LoadLevel()
{
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
				nextTile=Floor;
				m_SpawnPoint.x= static_cast<float>(horizontal);
				m_SpawnPoint.y = static_cast<float>(vertical);
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
