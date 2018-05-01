#pragma once
#include "../Core/Singleton.h"

class Scene;
class SceneManager final : public dae::Singleton<SceneManager>
{
public:

	void SetActive(const std::string& name);
	void AddScene(Scene* newScene, bool setActive = true);
	Scene* GetActiveScene() { return ActiveScene; };

	void Update(float deltaTime);
	void Render();

private:
	std::vector<Scene*> m_Scenes;
	Scene* ActiveScene;
};
