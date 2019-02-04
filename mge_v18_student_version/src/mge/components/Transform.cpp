#include "Transform.h"
#include "mge/core/GameObject.hpp"


Transform::Transform() : m_transform(glm::mat4(1))
{

}


Transform::~Transform()
{
	std::cout << "transform is destroyed" << std::endl;
}

glm::vec3 Transform::WorldPosition() const
{
	return glm::vec3(WorldTransform()[3]);
}

glm::vec3 Transform::LocalPosition() const
{
	return glm::vec3(m_transform[3]);
}

glm::mat4 Transform::LocalTransform() const
{
	return m_transform;
}

glm::mat4 Transform::WorldTransform() const
{
	if (m_gameObject->getParent() == nullptr) return m_transform;
	else return m_gameObject->getParent()->transform->WorldTransform() * m_transform;

}

void Transform::SetTransform(const glm::mat4& transform)
{
	m_transform = transform;
}

void Transform::SetLocalPosition(glm::vec3 position)
{
	m_transform[3] = glm::vec4(position, 1);
}

void Transform::Translate(glm::vec3 translation)
{
	SetTransform(glm::translate(m_transform, translation));
}

void Transform::Rotate(float angle, glm::vec3 axis)
{
	SetTransform(glm::rotate(m_transform,angle, axis));
}

void Transform::Scale(glm::vec3 scale)
{
	SetTransform(glm::scale(m_transform, scale));
}
