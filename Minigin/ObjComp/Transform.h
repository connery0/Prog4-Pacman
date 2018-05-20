#pragma once
#include "BaseObject.h"
#include <algorithm>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

#define RAD(x) x*0.0174533f
#define DEG(x) x*57.2958f

class Transform
{
public:
	Transform(BaseObject* parent): mParent(parent)
	{  
		if(parent->m_pParentObject)
		{
			hasParentTransform=true;
			mParRotation = parent->m_pParentObject->T()->GetRotation();
			mParPosition = parent->m_pParentObject->T()->GetPosition();
		}
	}
	~Transform(){ mParent=nullptr;}
	float GetRotation()
	{
		if (hasParentTransform)
			return mParRotation + mRotation;
		return mRotation;
	}
	float getRotationDeg()
	{
		return DEG(GetRotation());
	}
	glm::vec2 GetPosition()
	{
		glm::vec2 returnPos{};
		returnPos.x = cos(mParRotation)*mPosition.x - sin(mParRotation)*mPosition.y;
		returnPos.y = sin(mParRotation)*mPosition.x + cos(mParRotation)*mPosition.y;

		returnPos += mParPosition;
		return returnPos;
	}
	void updateFromParent(const float rotation, const glm::vec2 pos)
	{
		hasParentTransform=true;
		mParRotation=rotation;
		mParPosition=pos;
		
		if (mParent->m_ChildObjects.size()>0)
		{
			for (auto childObject : mParent->m_ChildObjects)
			{
				childObject->T()->updateFromParent(GetRotation(), GetPosition());
			}
		}
	}
	void SetTransform(const float x, const float y, const float rot,bool worldRotation=false)
	{
		mRotation = RAD(rot);
		if(worldRotation){mRotation-=mParRotation;}
		mPosition.x = x;
		mPosition.y = y;

		if (mParent->m_ChildObjects.size()>0)
		{
			for (auto childObject : mParent->m_ChildObjects)
			{
				childObject->T()->updateFromParent(GetRotation(), GetPosition());
			}
		}
	}
	void AddTransform(const float x, const float y, const float rot)
	{
		mRotation += RAD(rot);
		mPosition.x += x;
		mPosition.y += y;

		if (mParent->m_ChildObjects.size()>0)
		{
			for (auto childObject : mParent->m_ChildObjects)
			{
				childObject->T()->updateFromParent(GetRotation(), GetPosition());
			}
		}
	}
	void SetRotation(float rot)
	{
		SetTransform(mPosition.x,mPosition.y, rot);
	}
	void SetPosition(const float x,const float y)
	{
		SetTransform(x,y,mRotation);	
	}

private:
	BaseObject* mParent = nullptr;
	glm::vec2 mPosition{0,0};
	float mRotation{0};

	glm::vec2 mSize{0,0};
	glm::vec2 mScale{1,1};

	//parent transform values
	glm::vec2 mParPosition{0,0};
	float mParRotation{0};
public:
	bool hasParentTransform{false};

};
