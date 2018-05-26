#pragma once

#include "Scene.h"
#include "../ObjComp/ButtonGroupObj.h"

class SceneTitleScreen : public Scene
{
public:
	SceneTitleScreen();
	~SceneTitleScreen();
	virtual void Initialize() override;

private:
	std::shared_ptr<ButtonGroupComp> LevelSelectGroup;
	std::shared_ptr<ButtonGroupComp> Player1ControlGroup;
	std::shared_ptr<ButtonGroupComp> Player2ControlGroup;
	std::shared_ptr<ButtonGroupComp> ControllerOwnerGroup;
	std::shared_ptr<ButtonGroupComp> Player2GameModeGroup;

	std::shared_ptr<ButtonGroupComp> StartGameGroup;


};

