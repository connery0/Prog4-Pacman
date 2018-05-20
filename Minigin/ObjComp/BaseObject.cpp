#include "MiniginPCH.h"
#include "BaseObject.h"

#include "BaseComponent.h"
#include "Transform.h"


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
	
	safeDelete(m_Transform);

	m_ChildObjects.clear();
	m_pComponents.clear();

}

void BaseObject::Update(float deltaTime)
{
	for (std::shared_ptr<BaseComponent> comp : m_pComponents)
	{
		comp->Update(deltaTime);
	}

	for ( std::shared_ptr<BaseObject> obj : m_ChildObjects)
	{
		obj->Update(deltaTime);
	}
}

void BaseObject::Render() const
{
	for (std::shared_ptr<BaseComponent> comp: m_pComponents)
	{
		comp->Render();
	}
	for ( std::shared_ptr<BaseObject> obj : m_ChildObjects)
	{
		obj->Render();
	}
}

/**
 * \param newComponent (Can not be a transformComponent)
 * \return object, for easy chaining
 */
 void BaseObject::AddComponent(std::shared_ptr<BaseComponent> newComponent){
		newComponent->m_pParentObject = this;
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
	newChild->T()->updateFromParent(m_Transform->GetRotation(),m_Transform->GetPosition());
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
