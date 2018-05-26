#pragma once
#include "Scene.h"
class ButtonGroupComp;

class SceneSinglePlayerMap1 : public Scene
{
public:
	SceneSinglePlayerMap1();
	~SceneSinglePlayerMap1();
	virtual void Initialize() override;
	void Update(float deltaTime) override;
private:
	void addGhost(int prisonTile, std::string texture, std::shared_ptr<LevelObject> level);
	std::shared_ptr<ButtonGroupComp> backButton;
};

