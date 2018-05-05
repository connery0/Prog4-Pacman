#pragma once
#include <vector>
#include <memory>

class BaseComponent;
class TransformComponent;

class BaseObject:public std::enable_shared_from_this<BaseObject>
{
public:
	BaseObject();
	virtual ~BaseObject();

	virtual void Update(float deltaTime);
	virtual void Render()const;



	//Todo custom type version that makes the shared pointer

	std::shared_ptr<BaseObject> AddComponent(std::shared_ptr<BaseComponent> newComponent);
	void RemoveComponent(std::shared_ptr<BaseComponent> removeComp);

	void AddChild( std::shared_ptr<BaseObject> newChild);
	void RemoveChild( std::shared_ptr<BaseObject> oldChild);

	std::shared_ptr<TransformComponent> TransformComp() { return m_pTransform; }
	///Shorthand to recieve the transformComponent
	std::shared_ptr<TransformComponent> T() { return TransformComp(); }
	//To speed up setposition(getposition)
	void Tmove(float x=0,float y=0);


	bool remove = false;

protected:
	BaseObject* m_pParentObject;

	std::vector< std::shared_ptr<BaseObject>> m_ChildObjects;
	std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
	std::shared_ptr<TransformComponent> m_pTransform;


public:
	BaseObject(const BaseObject& other) = delete;
	BaseObject(BaseObject&& other) = delete;
	BaseObject& operator=(const BaseObject& other) = delete;
	BaseObject& operator=(BaseObject&& other) = delete;
};
