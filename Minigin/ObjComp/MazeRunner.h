#pragma once
#include "BaseComponent.h"
#include "LevelObject.h"
#include <thread>
#include <future>

class goalScript;

class MazeRunner :
	public BaseComponent
{
public:
	MazeRunner(goalScript&goalCalc,  float speed,std::vector<TileType> blockingTiles);
	
	void CalculateGoal();
	void Update(float deltaTime) override;

protected:
	float m_Speed=0;
	std::vector<TileType> m_blockingTiles;

	std::future<glm::vec2> m_Future;

	bool hasThread=false;
	std::thread goalCalculation;
	goalScript& calculationObject;


	std::shared_ptr<LevelObject> m_Maze;
	
};

