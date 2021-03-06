#pragma once
#include <vector>
#include <memory>

class Transform;
class BaseComponent;


class BaseObject
{
public:
	BaseObject();
	virtual ~BaseObject();

	virtual void Update(float deltaTime);
	virtual void Render()const;


	//Components
	template <typename _Ty, class ..._Types>
	std::shared_ptr<_Ty> CreateChildComponent(_Types&& ..._Args);
	void AddComponent(std::shared_ptr<BaseComponent> newComponent);
	void RemoveComponent(std::shared_ptr<BaseComponent> removeComp);
	template<class T>
	std::shared_ptr<T> GetComponent(bool searchChildren = false);
	template<class T>
	std::vector<std::shared_ptr<T>> GetComponents(bool searchChildren = false);

	//ChildObjects	
	template <typename _Ty, class ..._Types>
	std::shared_ptr<_Ty> CreateChildObj(_Types&& ..._Args);
	void AddChild(std::shared_ptr<BaseObject> newChild);
	void RemoveChild(std::shared_ptr<BaseObject> oldChild);

	//Transform Access
	Transform* T() const {return m_Transform;}
	void Tadd(float x,float y,float rot=0);
	void Tset(float x, float y, float rot=0);
	bool CollidesWith(std::shared_ptr<BaseObject>other);
	bool CollidesWithPoint(int x, int y);

	//Management variables
	bool remove = false;
	bool isActive=true;
	bool isPaused = false;//only stop update, but keep rendering
friend Transform;
protected:
	BaseObject* m_pParentObject;
	Transform* m_Transform;

	std::vector< std::shared_ptr<BaseObject>> m_ChildObjects;
	std::vector<std::shared_ptr<BaseComponent>> m_pComponents;

	BaseObject(const BaseObject& other) = delete;
	BaseObject(BaseObject&& other) = delete;
	BaseObject& operator=(const BaseObject& other) = delete;
	BaseObject& operator=(BaseObject&& other) = delete;
	
};

template <typename _Ty, class ... _Types>
std::shared_ptr<_Ty> BaseObject::CreateChildComponent(_Types&&... _Args)
{
	auto newComponent = std::make_shared<_Ty>(_Args...);
	AddComponent(std::dynamic_pointer_cast<BaseComponent>(newComponent));
	return newComponent;
}

template <class T>
std::shared_ptr<T> BaseObject::GetComponent(const bool searchChildren)
{
	const type_info& ti = typeid(T);
	for (std::shared_ptr<BaseComponent> component : m_pComponents)
	{
		if (component && typeid(*component) == ti)
			return std::dynamic_pointer_cast<T>(component);
	}

	if (searchChildren)
	{
		for (auto child : m_ChildObjects)
		{
			if (child->GetComponent<T>(searchChildren) != nullptr)
				return child->GetComponent<T>(searchChildren);
		}
	}
	return nullptr;
}

template <class T>
std::vector<std::shared_ptr<T>> BaseObject::GetComponents(bool searchChildren)
{
	std::vector<std::shared_ptr<T>> returnVector;
	const type_info& ti = typeid(T);
	for (std::shared_ptr<BaseComponent> component : m_pComponents)
	{
		if (component && typeid(*component) == ti)
			returnVector.push_back(std::dynamic_pointer_cast<T>(component));
	}

	if (searchChildren)
	{
		for (auto child : m_ChildObjects)
		{
			std::vector<std::shared_ptr<T>> childComponents = child->GetComponents<T>(searchChildren);
			if(childComponents.size()>0)
			{
				for(std::shared_ptr<T> comp:childComponents)
				{
					returnVector.push_back(std::dynamic_pointer_cast<T>(comp));
				}
			}
		}
	}
	return returnVector;
}

template <typename _Ty, class ... _Types>
std::shared_ptr<_Ty> BaseObject::CreateChildObj(_Types&&... _Args)
{
	std::shared_ptr<_Ty> newChild = std::make_shared<_Ty>(_Args...);
	AddChild(newChild);
	return newChild;
}
