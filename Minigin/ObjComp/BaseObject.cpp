#include "MiniginPCH.h"
#include "BaseObject.h"

#include "BaseComponent.h"


BaseObject::BaseObject():
	m_pParentObject(nullptr),
	m_ChildObjects(std::vector<std::shared_ptr<BaseObject>>()),
	m_pComponents(std::vector<std::shared_ptr<BaseComponent>>())
{
}

BaseObject::~BaseObject()
{
	for (auto child : m_ChildObjects)
	{
		child->m_pParentObject=nullptr;
	}
	m_pParentObject=nullptr;

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
 std::shared_ptr<BaseObject> BaseObject::AddComponent(std::shared_ptr<BaseComponent> newComponent){
	//Can only have one transformComponent
	if(typeid(newComponent)!= typeid(std::shared_ptr<TransformComponent>))
	{
		newComponent->m_pParentObject = this;
		m_pComponents.push_back(newComponent);
	}
	return shared_from_this();
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
}

void BaseObject::RemoveChild( std::shared_ptr<BaseObject> oldChild)
{
	oldChild->m_pParentObject = nullptr;
	m_ChildObjects.erase(find(m_ChildObjects.begin(), m_ChildObjects.end(), oldChild));
}