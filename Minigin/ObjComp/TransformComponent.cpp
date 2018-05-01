#include "MiniginPCH.h"
#include "TransformComponent.h"


void TransformComponent::SetPosition(const float x, const float y, const float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
}

void TransformComponent::SetRotation(const float x, const float y, const float z)
{
	mRotation.x = x;
	mRotation.y = y;
	mRotation.z = z;
}

void TransformComponent::SetScale(float x, float y, float z)
{
	mScale.x = x;
	mScale.y = y;
	mScale.z = z;
}
