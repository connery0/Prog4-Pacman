#pragma once

class BaseObject;

class BaseComponent
{
public:
	BaseComponent(){};
	virtual ~BaseComponent(){};

	virtual void Update(float deltaTime) { (void)deltaTime; };
	virtual void Render()const {};
	virtual void addParent(BaseObject* parentObj){m_pParentObject=parentObj;};
	bool isActive = true;
	bool isPaused = false;//only stop update, but keep rendering
protected:
	BaseObject* m_pParentObject;

private:
	friend class BaseObject;

};

