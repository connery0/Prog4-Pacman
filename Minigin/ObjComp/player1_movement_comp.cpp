#include "MiniginPCH.h"
#include "Player1MovementComp.h"
#include "BaseObject.h"
#include "Transform.h"


void player1_movement_comp::Initialize()
{
	if (input == nullptr)
	{
		if (m_pParentObject)
		{
			input = m_pParentObject->GetComponent<InputComp>();
			if(!input)
			{
				input = m_pParentObject->CreateChildComponent<InputComp>();
			}
		}
		else
		{
			return;
		}
	}

	input->addInput(MoveLeft,'A');
	input->addInput(MoveRight, 'D');
	input->addInput(MoveUp, 'W');
	input->addInput(MoveDown, 'S');

	m_Initialized=true;
}

void player1_movement_comp::Update(float deltaTime)
{
	if(!m_Initialized)
		Initialize();

	if(m_Initialized)//Do not try to update if initialize failed
	{
		float xSpeed=0;
		float ySpeed = 0;
		
		if(input->isDown(MoveLeft))
			xSpeed-=1;
		if (input->isDown(MoveRight))
			xSpeed += 1;
		if (input->isDown(MoveUp))
			ySpeed -= 1;
		if (input->isDown(MoveDown))
			ySpeed += 1;


		m_pParentObject->T()->AddTransform(speedMul*xSpeed*deltaTime,speedMul*ySpeed*deltaTime,0);
	}
}

