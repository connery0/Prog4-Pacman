#pragma once
#include "../MiniginPCH.h"
#include <stdlib.h> 

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <future>

class goalScript
{
public:
	virtual ~goalScript() = default;

	virtual void CalculateGoalAsync(BaseObject* Parent, std::promise<std::pair<float, float>> && p)
	{
		(void) Parent;
		p.set_value(std::make_pair(1.f,1.f));
	}
	virtual std::pair<float,float> CalculateGoalSync(BaseObject* Parent)
	{
		(void)Parent;
		return std::make_pair(1.f, 1.f);
	}
};
