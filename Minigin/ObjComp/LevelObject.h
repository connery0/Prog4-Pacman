#pragma once
#include "BaseObject.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "vector"
#include "Texture2D.h"

//Changes need to be added to mazerunner map!
enum TileType{
	Wall='w',
	Floor='0',
	Prison='1',
	Coin='2',
	Powerup='3',
	Fruit='4',
	SpawnPoint='s'
};


class LevelObject:public BaseObject
{
public:
	LevelObject(std::string FileName);
	void Render() const override;
	void LoadLevel();
	void LoadLevel(std::string FileName);
	
	TileType getTile(float x,float y);
	TileType pickupTile(float x, float y);
	
	float getBorder(float p1, float p2);


protected:
	//std::pair<float, float> m_Size {21,17};
	const int m_Width = 21;
	const int m_Height=17;

	const int m_TileSize=50;

	const std::string FileNameWall ="Wall2.png";
	std::shared_ptr<dae::Texture2D> t_Wall;
	const std::string FileNameFloor = "Floor.png";
	std::shared_ptr<dae::Texture2D> t_Floor;
	const std::string FileNamePrison = "Prison.png";
	std::shared_ptr<dae::Texture2D> t_Prison;
	const std::string FileNameCoin = "Coin.png";
	std::shared_ptr<dae::Texture2D> t_Coin;
	const std::string FileNamePowerup = "Powerup.png";
	std::shared_ptr<dae::Texture2D> t_Powerup;
	const std::string FileNameFruit = "Prison.png"; //todo: Fruit for extra points (in level or as seperate actor?)
	std::shared_ptr<dae::Texture2D> t_Fruit;

	std::vector<TileType>m_Tiles;
	std::string m_LevelString;
};
