#include "MiniginPCH.h"
#include "Scene.h"
#include <algorithm>
#include "../ObjComp/BaseObject.h"

unsigned int Scene::idCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
}

void Scene::Add(std::shared_ptr<BaseObject> object)
{
	mObjects.push_back(object);
}

void Scene::Remove( std::shared_ptr<BaseObject> object)
{
	auto it = find(mObjects.begin(), mObjects.end(), object);
	if (it != mObjects.end()) {
		object->remove = true;
	}
}

void Scene::Update(float deltaTime)
{
	bool removeObjects = false;
	for (auto gameObject : mObjects)
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
		mObjects.erase(
			std::remove_if(mObjects.begin(), mObjects.end(),[]( std::shared_ptr<BaseObject> object) {return object->remove;})
			, mObjects.end()
		);
	}

}

void Scene::Render() const
{
	for (const auto gameObject : mObjects)
	{
		if(!gameObject->remove && gameObject->isActive)
			gameObject->Render();
	}
}

