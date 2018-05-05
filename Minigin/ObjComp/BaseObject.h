#pragma once
#include <vector>
#include <memory>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)


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

	bool remove = false;

protected:
	BaseObject* m_pParentObject;

	std::vector< std::shared_ptr<BaseObject>> m_ChildObjects;
	std::vector<std::shared_ptr<BaseComponent>> m_pComponents;


public:
	BaseObject(const BaseObject& other) = delete;
	BaseObject(BaseObject&& other) = delete;
	BaseObject& operator=(const BaseObject& other) = delete;
	BaseObject& operator=(BaseObject&& other) = delete;


	//Transform - part of every gameObject
private:
	glm::vec3 mPosition;
	double mRotation=0;
	glm::vec3 mScale;
public:

	const glm::vec3 TGetPosition(){
		if (m_pParentObject)
			return m_pParentObject->TGetPosition() + mPosition;
		else
			return mPosition;
			};
	
	const double TGetRotation() const { 
		if(m_pParentObject)
			return m_pParentObject->TGetRotation()+mRotation;
		else		
			return mRotation; 
			}

	const glm::vec3& TGetScale() const { return mScale; }

	void TSetPosition(float x, float y, float z = 0.f){
		mPosition.x = x;
		mPosition.y = y;
		mPosition.z = z;
	};

	void TSetRotation(double rotationDeg){mRotation=rotationDeg;};
	void TSetScale(float x, float y, float z = 0.f){
		mScale.x = x;
		mScale.y = y;
		mScale.z = z;
	};
	
};
