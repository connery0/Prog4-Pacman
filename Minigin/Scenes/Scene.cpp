#include "MiniginPCH.h"
#include "Scene.h"
#include <algorithm>
#include "../ObjComp/BaseObject.h"

unsigned int Scene::idCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(BaseObject* object)
{
	mObjects.push_back(object);
}

void Scene::Remove(BaseObject* object)
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
		if (!gameObject->remove) {
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
			std::remove_if(mObjects.begin(), mObjects.end(),[](BaseObject* object) {return object->remove;})
			, mObjects.end()
		);
	}

}

void Scene::Render() const
{
	for (const auto gameObject : mObjects)
	{
		if(!gameObject->remove) gameObject->Render();
	}
}

