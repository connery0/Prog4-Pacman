#pragma once
#include "Scene.h"

class SceneSinglePlayer : public Scene
{
public:
	SceneSinglePlayer();
	~SceneSinglePlayer();
	virtual void Initialize() override;
};

