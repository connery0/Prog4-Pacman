#pragma once
#include "../Core/Singleton.h"
#include <memory>
class Scene;
class SceneManager final : public dae::Singleton<SceneManager>
{
public:
	
	~SceneManager()
	{
		m_Scenes.clear();
		ActiveScene.reset();
	}

	void SetActive(const std::string& name);
	void AddScene(std::shared_ptr<Scene> newScene, bool setActive = true);
	

	//TODO:  add<sceneType>("name",args) -> adds sharedPtr (and returns>)
	//TODO:  Always as active scene (can be reset manually later)/second version, addActive?
	/*template <typename S>
	void Add<S>();*/
	
	std::shared_ptr<Scene> GetActiveScene() { return ActiveScene; };

	void Update(float deltaTime);
	void Render();

private:
	std::vector<std::shared_ptr<Scene> > m_Scenes;
	std::shared_ptr<Scene> ActiveScene;
};
