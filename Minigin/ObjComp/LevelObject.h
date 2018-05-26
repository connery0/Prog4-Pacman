#pragma once
#include "BaseObject.h"

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

	TileType getTile(std::pair<float, float> pos);
	TileType getTile(float x,float y);
	TileType pickupTile(std::pair<float, float> pos);
	TileType pickupTile(float x, float y);
	
	float getBorder(float p1, float p2);
	static std::pair<int, int> GetTileCoord(std::pair<float,float> testCoord);

protected:

	static const int m_Width = 21;
	static const int m_Height=17;
	static const int m_TileSize=50;

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
	const std::string FileNameFruit = "Fruit.png"; //todo: Fruit for extra points (in level or as seperate actor?)
	std::shared_ptr<dae::Texture2D> t_Fruit;

	std::vector<TileType>m_Tiles;
	std::string m_LevelString;
};
