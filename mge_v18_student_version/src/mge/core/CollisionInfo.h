#pragma once
#include <vector>
#include "GameObject.hpp"
#include <glm.hpp>

class CollisionInfo
{
public:
	std::vector<GameObject*> colliders;
	std::vector<glm::vec2> hitPoints;

	~CollisionInfo();
};

