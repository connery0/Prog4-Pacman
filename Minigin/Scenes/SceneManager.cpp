#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
#include "../Core/InputManager.h"


void SceneManager::Update(float deltaTime)
{
	if(ActiveScene!=nullptr)
		ActiveScene->Update(deltaTime);
}

void SceneManager::Render()
{
	if (ActiveScene != nullptr)
		ActiveScene->Render();
}

void SceneManager::SetActive(const std::string& name)
{
	dae::InputManager::GetInstance().Destroy();
	auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [&name](std::shared_ptr<Scene>  s)-> bool {return s->CompareName(name); });
	
	if (it != m_Scenes.end()) {
		ActiveScene = *it;
	}
}

void SceneManager::AddScene(std::shared_ptr<Scene> newScene, bool setActive)
{
	dae::InputManager::GetInstance().Destroy();
	auto it = find(m_Scenes.begin(), m_Scenes.end(), newScene);
	if(it==m_Scenes.end())
	{
		m_Scenes.push_back(newScene);
		if (setActive|| ActiveScene==nullptr) { ActiveScene = newScene; }
	}
}

void SceneManager::RemoveActiveScene(std::string nextScene)
{
	auto toRemove = ActiveScene;
	SetActive(nextScene);
	m_Scenes.erase(std::remove(m_Scenes.begin(), m_Scenes.end(), toRemove), m_Scenes.end());
}

void SceneManager::Destroy()
{
	m_Scenes.clear();
	ActiveScene=nullptr;
}


std::shared_ptr<Scene> SceneManager::GetActiveScene()
{
	return ActiveScene;
}
