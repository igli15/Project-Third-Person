#pragma once
#include <vector>
#include "GameObject.hpp"
#include <glm.hpp>

class CollisionInfo
{
public:
	GameObject* collider;
	glm::vec2 hitPoint;
	glm::vec2 distance;
	glm::vec2 normal;
	~CollisionInfo();
};

