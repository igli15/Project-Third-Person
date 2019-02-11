#include "RotatingComponent.h"
#include "mge/core/GameObject.hpp"


RotatingComponent::RotatingComponent()
{
}


RotatingComponent::~RotatingComponent()
{
}

void RotatingComponent::Update(float timeStep)
{
	m_gameObject->transform->Rotate(timeStep * glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
}
