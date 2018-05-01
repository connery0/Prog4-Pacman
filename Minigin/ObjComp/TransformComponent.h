#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include "BaseComponent.h"
#pragma warning(pop)


class TransformComponent final:public BaseComponent
{	
		
private:
	glm::vec3 mPosition;
	glm::vec3 mRotation;
	glm::vec3 mScale;

public:
	const glm::vec3& GetPosition() const { return mPosition; }
	const glm::vec3& GetRotation() const { return mRotation; }
	const glm::vec3& GetScale() const { return mScale; }

	void SetPosition(float x, float y, float z=0.f);
	void SetRotation(float x, float y,float z =0.f);
	void SetScale(float x, float y, float z = 0.f);
};
