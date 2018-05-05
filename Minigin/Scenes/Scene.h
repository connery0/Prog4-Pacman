#pragma once
#include "SceneManager.h"
#include <memory>

class BaseObject;
class Scene
{
public:
	Scene(const std::string& name);

	void Add( std::shared_ptr<BaseObject> object);
	void Remove( std::shared_ptr<BaseObject> object);

	void Update(float deltaTime);
	void Render() const;
	bool CompareName(const std::string& compareName) const { return m_Name.compare(compareName)==0; }
	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;


private: 
		
	std::string m_Name{};
	std::vector <std::shared_ptr<BaseObject>> mObjects;

	static unsigned int idCounter; 
};
