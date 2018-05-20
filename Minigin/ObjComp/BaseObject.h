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

	//Todo: Remove?
	void AddComponent(std::shared_ptr<BaseComponent> newComponent);
	void RemoveComponent(std::shared_ptr<BaseComponent> removeComp);

	template <typename _Ty, class ..._Types>
	std::shared_ptr<_Ty> CreateChildComponent(_Types && ..._Args) {
		auto newComponent = std::make_shared<_Ty>(_Args...);
		newComponent->m_pParentObject = this;
		m_pComponents.push_back(newComponent);
		return newComponent;
	}
	
	void AddChild( std::shared_ptr<BaseObject> newChild);
	void RemoveChild( std::shared_ptr<BaseObject> oldChild);
	
	template <typename _Ty, class ..._Types>
	std::shared_ptr<_Ty> CreateChildObj (_Types && ..._Args) {
		std::shared_ptr<_Ty> newChild = std::make_shared<_Ty>(_Args...);
		m_ChildObjects.push_back(newChild);
		newChild->m_pParentObject=this;

		return newChild;
	}

	bool remove = false;


	Transform* T() const {return m_Transform;}
	void Tadd(float x,float y,float rot=0);
	void Tset(float x, float y, float rot=0);


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


	//Transform - part of every gameObject
//private:
//	glm::vec3 mPosition;
//	double mRotation=0;
//	glm::vec3 mScale;
//public:
//
//	const glm::vec3 TGetPosition(){
//		if (m_pParentObject)
//			return m_pParentObject->TGetPosition() + mPosition;
//		else
//			return mPosition;
//			};
//	
//	const double TGetRotation() const { 
//		if(m_pParentObject)
//			return m_pParentObject->TGetRotation()+mRotation;
//		else		
//			return mRotation; 
//			}
//
//	const glm::vec3& TGetScale() const { return mScale; }
//
//	void TSetPosition(float x, float y, float z = 0.f){
//		mPosition.x = x;
//		mPosition.y = y;
//		mPosition.z = z;
//	};
//
//	void TSetRotation(double rotationDeg){mRotation=rotationDeg;};
//	void TSetScale(float x, float y, float z = 0.f){
//		mScale.x = x;
//		mScale.y = y;
//		mScale.z = z;
//	};
	
};
