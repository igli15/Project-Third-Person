#pragma once
#include "ColliderComponent.hpp"
#include <glm.hpp>
class SphereCollider :public ColliderComponent
{
public:
	void Update(float timeSteps) override;
	glm::vec2 GetWorld2Dposition();
protected:
	glm::vec2 oldPos;
};
