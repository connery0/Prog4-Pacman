#pragma once
#include "../MiniginPCH.h"
#include <stdlib.h> 

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#include <future>
#pragma warning(pop)

class goalScript
{
public:	
	void CalculateGoal(BaseObject* Parent, std::promise<glm::vec2> && p)
	{
		(void) Parent;
		p.set_value(glm::vec2{1,1});
	}	
};
