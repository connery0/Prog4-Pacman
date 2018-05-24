#include "MiniginPCH.h"
#include "Scene.h"
#include <algorithm>
#include "../ObjComp/BaseObject.h"
#include "../ObjComp/BaseComponent.h"
#include "../ObjComp/MazeRunner.h"

unsigned int Scene::idCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
}

void Scene::Add(std::shared_ptr<BaseObject> object)
{
	m_Objects.push_back(object);
}

void Scene::Remove( std::shared_ptr<BaseObject> object)
{
	auto it = find(m_Objects.begin(), m_Objects.end(), object);
	if (it != m_Objects.end()) {
		object->remove = true;
	}
}

void Scene::Update(float deltaTime)
{
	if(!isInitialized){
		Initialize();
		isInitialized=true;
	}

	
	/*Allow mazerunners to find goal before update cycle*/
	for (auto gameObject : m_Objects)
	{
		std::shared_ptr<MazeRunner> runner =gameObject->GetComponent<MazeRunner>(true);
		if(runner!=nullptr)
			runner->CalculateGoal();
	}

	/*Update all objects*/
	bool removeObjects = false;
	for (auto gameObject : m_Objects)
	{
		if (!gameObject->remove && gameObject->isActive && !gameObject->isPaused) {
			gameObject->Update(deltaTime);
		}
		else
		{
			removeObjects = true;
		};
	}
	if(removeObjects)
	{
		m_Objects.erase(
			std::remove_if(m_Objects.begin(), m_Objects.end(),[]( std::shared_ptr<BaseObject> object) {return object->remove;})
			, m_Objects.end()
		);
	}

}

void Scene::Render() const
{
	for (const auto gameObject : m_Objects)
	{
		if(!gameObject->remove && gameObject->isActive)
			gameObject->Render();
	}
}

