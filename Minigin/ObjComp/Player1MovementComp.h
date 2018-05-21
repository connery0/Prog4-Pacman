#pragma once
#include "BaseComponent.h"
#include "InputComp.h"
#include <memory>

class player1_movement_comp :public BaseComponent
{

	void Init();
	void Update(float deltaTime) override;

	float speedMul = 100;
		
protected:
	enum Actions
	{
		MoveLeft,MoveRight,MoveUp,MoveDown
	};


private:
	std::shared_ptr<InputComp> input=nullptr;
	bool m_Initialized=false;
};

