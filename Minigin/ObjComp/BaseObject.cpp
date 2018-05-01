#include "MiniginPCH.h"
#include "BaseObject.h"

#include "BaseComponent.h"
#include "../ObjComp/TransformComponent.h"


BaseObject::BaseObject():
	m_pParentObject(nullptr),
	m_ChildObjects(std::vector<BaseObject*>()),
	m_pComponents(std::vector<BaseComponent*>()),
	m_pTransform(nullptr)
{
	m_pTransform = new TransformComponent();
	m_pComponents.push_back(m_pTransform);
}

void BaseObject::Update(float deltaTime)
{
	for (BaseComponent* comp : m_pComponents)
	{
		comp->Update(deltaTime);
	}

	for (BaseObject* obj : m_ChildObjects)
	{
		obj->Update(deltaTime);
	}
}

void BaseObject::Render() const
{
	for (BaseComponent* comp: m_pComponents)
	{
		comp->Render();
	}
	for (BaseObject* obj : m_ChildObjects)
	{
		obj->Render();
	}
}

/**
 * \param newComponent (Can not be a transformComponent)
 * \return object, for easy chaining
 */
BaseObject* BaseObject::AddComponent(BaseComponent* newComponent){
	//Can only have one transformComponent
	if(typeid(newComponent)!= typeid(TransformComponent))
	{
		newComponent->m_pParentObject = this;
		m_pComponents.push_back(newComponent);
	}else if(m_pTransform==nullptr)
	{
		m_pTransform = static_cast<TransformComponent*>(newComponent);
		m_pComponents.push_back(newComponent);}
	return this;
}

void BaseObject::RemoveComponent(BaseComponent* removeComp)
{
	m_pComponents.erase(find(m_pComponents.begin(), m_pComponents.end(), removeComp));
	removeComp->m_pParentObject = nullptr;
}

void BaseObject::AddChild(BaseObject* newChild)
{
	m_ChildObjects.push_back(newChild);
	newChild->m_pParentObject = this;
}

void BaseObject::RemoveChild(BaseObject* oldChild)
{
	oldChild->m_pParentObject = nullptr;
	m_ChildObjects.erase(find(m_ChildObjects.begin(), m_ChildObjects.end(), oldChild));
}

