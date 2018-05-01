#pragma once
#include <vector>

class BaseComponent;
class TransformComponent;

class BaseObject
{
public:
	BaseObject();
	virtual void Update(float deltaTime);
	virtual void Render()const;

	BaseObject* AddComponent(BaseComponent* newComponent);
	void RemoveComponent(BaseComponent* removeComp);

	void AddChild(BaseObject* newChild);
	void RemoveChild(BaseObject* oldChild);

	TransformComponent* TransformComp() { return m_pTransform; }
	///Shorthand to recieve the transformComponent
	TransformComponent* T() { return TransformComp(); }


	bool remove = false;

protected:
	BaseObject* m_pParentObject;
	std::vector<BaseObject*> m_ChildObjects;
	std::vector<BaseComponent*> m_pComponents;
	TransformComponent* m_pTransform;


public:
	virtual ~BaseObject() = default;
	BaseObject(const BaseObject& other) = delete;
	BaseObject(BaseObject&& other) = delete;
	BaseObject& operator=(const BaseObject& other) = delete;
	BaseObject& operator=(BaseObject&& other) = delete;
};
