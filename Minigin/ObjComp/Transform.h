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
	std::pair<float, float> GetPosition()
	{
		std::pair<float, float> returnPos{};
		returnPos.first = cos(mParRotation)*mPosition.first - sin(mParRotation)*mPosition.second;
		returnPos.second = sin(mParRotation)*mPosition.first + cos(mParRotation)*mPosition.second;

		returnPos.first += mParPosition.first;
		returnPos.second+= mParPosition.second;
		return returnPos;
	}
	void updateFromParent(const float rotation, const std::pair<float, float> pos)
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
		mPosition.first = x;
		mPosition.second = y;

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
		mPosition.first += x;
		mPosition.second += y;

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
		SetTransform(mPosition.first,mPosition.second, rot);
	}
	void SetPosition(const float x,const float y)
	{
		SetTransform(x,y,mRotation);	
	}
	void SetPosition(const std::pair<float, float> pos)
	{
		SetTransform(pos.first, pos.second, mRotation);
	}

	std::pair<float, float> GetSize(){return mSize;}
	void SetSize(const float x, const float y) { mSize.first=x;mSize.second =y;}


private:
	BaseObject* mParent = nullptr;
	std::pair<float, float> mPosition{0.f,0.f };
	float mRotation{0};

	std::pair<float, float> mSize{0.f,0.f};
	std::pair<float, float> mScale{1.f,1.f};

	//parent transform values
	std::pair<float, float> mParPosition{0.f,0.f};
	float mParRotation{0};
public:
	bool hasParentTransform{false};

};
