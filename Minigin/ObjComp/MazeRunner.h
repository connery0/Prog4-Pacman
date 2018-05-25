#pragma once
#include "BaseComponent.h"
#include "LevelObject.h"
#include <thread>
#include <future>
#include <map>

class goalScript;

class MazeRunner :
	public BaseComponent
{
public:
	MazeRunner(std::shared_ptr<LevelObject>maze, goalScript* goalCalc,  float speed,bool async=false);
	~MazeRunner()
	{
		if(goalCalculation.joinable())
			goalCalculation.join();
	}
	
	void CalculateGoal(float deltaTime);
	void Update(float deltaTime) override;

	std::map<TileType, bool>m_DoesTileBlock
	{
		std::make_pair(TileType::Wall, true),
		std::make_pair(TileType::Floor, false),
		std::make_pair(TileType::Prison, false),
		std::make_pair(TileType::Coin, false),
		std::make_pair(TileType::Powerup, false),
		std::make_pair(TileType::Fruit, false),
		std::make_pair(TileType::SpawnPoint, false),
	};
protected:
	float m_Speed=0;

	std::shared_ptr<LevelObject> m_Maze;
	std::pair<float, float>m_Goal{ 0.f,0.f };

	bool isAsync=false;
	std::future<std::pair<float, float>> m_Future;
	std::thread goalCalculation;
	goalScript* calculationObject;
	const float goalUpdateDelay=0.5f;
	float timeSinceLastGoal = 0.f;
};

