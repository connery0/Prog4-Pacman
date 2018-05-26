#pragma once
#include "Scene.h"
class ButtonGroupComp;

class SceneSinglePlayerMap2 : public Scene
{
public:
	SceneSinglePlayerMap2();
	~SceneSinglePlayerMap2();
	virtual void Initialize() override;
	void Update(float deltaTime) override;
private:
	std::shared_ptr<ButtonGroupComp> backButton;
};

