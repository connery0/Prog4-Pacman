#pragma once

class BaseObject;

class BaseComponent
{
public:
	BaseComponent();
	virtual ~BaseComponent();

	virtual void Update(float deltaTime) { (void)deltaTime; };
	virtual void Render()const {};


protected:
	BaseObject* m_pParentObject;

private:
	friend class BaseObject;

};
