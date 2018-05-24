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
	template <class T>
	std::shared_ptr<T> getChild();;
	template <class T>
	std::vector<std::shared_ptr<T>> getChildren();;


	virtual void Initialize()=0;

	void Update(float deltaTime);
	void Render() const;
	bool CompareName(const std::string& compareName) const { return m_Name.compare(compareName)==0; }
	virtual ~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;


	template <typename _Ty, class ..._Types>
	std::shared_ptr<_Ty>  AddNew(_Types && ..._Args){ 
		auto pointer = std::make_shared<_Ty>(_Args...);
		m_Objects.push_back(pointer);
		return pointer;
		};



protected: 
	bool isInitialized=false;	
	std::string m_Name{};
	std::vector <std::shared_ptr<BaseObject>> m_Objects;

	static unsigned int idCounter; 
};

template <class T>
std::shared_ptr<T> Scene::getChild()
{
	const type_info& ti = typeid(T);
	for (std::shared_ptr<BaseComponent> childObject : m_Objects)
	{
		if (childObject && typeid(*childObject) == ti)
			return std::dynamic_pointer_cast<T>(childObject);
	}
	return nullptr;
}

template <class T>
std::vector<std::shared_ptr<T>> Scene::getChildren()
{
	const type_info& ti = typeid(T);
	std::vector<std::shared_ptr<T>> returnVector;

	for (std::shared_ptr<BaseComponent> childObject : m_Objects)
	{
		if (childObject && typeid(*childObject) == ti)
			returnVector.push_back(std::dynamic_pointer_cast<T>(childObject));
	}
	return returnVector;
}
