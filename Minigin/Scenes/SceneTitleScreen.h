#pragma once

#include "Scene.h"

class SceneTitleScreen : public Scene
{
public:
	SceneTitleScreen();
	~SceneTitleScreen();
	virtual void Initialize() override;
};

