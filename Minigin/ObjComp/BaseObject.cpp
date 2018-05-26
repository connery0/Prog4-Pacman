#include "MiniginPCH.h"
#include "BaseObject.h"


BaseObject::BaseObject():
	m_pParentObject(nullptr),
	m_ChildObjects(std::vector<std::shared_ptr<BaseObject>>()),
	m_pComponents(std::vector<std::shared_ptr<BaseComponent>>()),
	m_Transform(new Transform(this))
{
}

BaseObject::~BaseObject()
{
	for (auto child : m_ChildObjects)
	{
		child->m_pParentObject=nullptr;
	}
	m_pParentObject=nullptr;
	
	SafeDelete(m_Transform);

	m_ChildObjects.clear();
	m_pComponents.clear();

}

void BaseObject::Update(float deltaTime)
{
	for (std::shared_ptr<BaseComponent> comp : m_pComponents)
	{
		if(comp->isActive && !comp->isPaused)
			comp->Update(deltaTime);
	}

	for ( std::shared_ptr<BaseObject> obj : m_ChildObjects)
	{
		if(obj->isActive && !obj->isPaused)
			obj->Update(deltaTime);
	}
}

void BaseObject::Render() const
{
	for (std::shared_ptr<BaseComponent> comp: m_pComponents)
	{
		if(comp->isActive && !comp->isPaused)
			comp->Render();
	}
	for ( std::shared_ptr<BaseObject> obj : m_ChildObjects)
	{
		if (obj->isActive && !obj->isPaused)
			obj->Render();
	}
}

/**
 * \param newComponent (Can not be a transformComponent)
 * \return object, for easy chaining
 */
 void BaseObject::AddComponent(std::shared_ptr<BaseComponent> newComponent){
		newComponent->addParent(this);
		m_pComponents.push_back(newComponent);
}

void BaseObject::RemoveComponent(std::shared_ptr<BaseComponent> removeComp)
{
	m_pComponents.erase(find(m_pComponents.begin(), m_pComponents.end(), removeComp));
	removeComp->m_pParentObject = nullptr;
}

void BaseObject::AddChild( std::shared_ptr<BaseObject> newChild)
{
	m_ChildObjects.push_back(newChild);
	newChild->m_pParentObject = this;
	T()->updateChild(newChild);
}

void BaseObject::RemoveChild( std::shared_ptr<BaseObject> oldChild)
{
	oldChild->m_pParentObject = nullptr;
	m_ChildObjects.erase(find(m_ChildObjects.begin(), m_ChildObjects.end(), oldChild));
}

void BaseObject::Tadd(float x, float y, float rot)
{
	m_Transform->AddTransform(x, y, rot);
}

void BaseObject::Tset(float x, float y, float rot)
{
	m_Transform->SetTransform(x, y, rot);
}

bool BaseObject::CollidesWith(std::shared_ptr<BaseObject> other)
{
	if(other->T()==m_Transform) return false; //Don't collide with yourself

	auto otherT = other->T();
	//Check if the center point overlaps with the other object
	return 
		(m_Transform->GetPosition().first>otherT->GetPosition().first-otherT->GetSize().first/2)
	&&	(m_Transform->GetPosition().first<otherT->GetPosition().first + otherT->GetSize().first / 2)
	&&	(m_Transform->GetPosition().second>otherT->GetPosition().second- otherT->GetSize().second / 2)
	&&	(m_Transform->GetPosition().second<otherT->GetPosition().second + otherT->GetSize().second / 2);

}
