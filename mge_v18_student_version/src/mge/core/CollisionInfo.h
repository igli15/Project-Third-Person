#pragma once
#include "mge/core/GameObject.hpp"

class CollisionInfo
{
public:
	GameObject* collider;
	glm::vec2 hitPoint;

	CollisionInfo();
	~CollisionInfo();
};

