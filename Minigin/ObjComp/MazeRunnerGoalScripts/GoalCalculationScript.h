#pragma once
#include "../MiniginPCH.h"
#include <stdlib.h> 


#include <future>

class goalScript
{
public:
	virtual ~goalScript() = default;

	virtual void CalculateGoalAsync(BaseObject* Parent, float TimePassed, std::promise<std::pair<float, float>> && p)
	{
		p.set_value(CalculateGoalSync(Parent,TimePassed));
	}
	virtual std::pair<float,float> CalculateGoalSync(BaseObject* Parent,float TimePassed)
	{
		(void)Parent,TimePassed;
		return std::make_pair(1.f, 1.f);
	}
};
