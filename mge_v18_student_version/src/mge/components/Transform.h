#pragma once

#include "glm.hpp"
#include "../core/Component.h"

class Transform :
	public Component
{
public:
	Transform();
	virtual ~Transform();

	virtual void OnDestroy() override;

	glm::vec3 WorldPosition() const;
	glm::vec3 LocalPosition() const; 

	glm::mat4 LocalTransform() const;
	glm::mat4 WorldTransform() const;

	void SetTransform(const glm::mat4& transform);

	void SetLocalPosition(glm::vec3);

	void SetScale(glm::vec3 scale);
	glm::vec3 GetScale();
	void Translate(glm::vec3 translation);
	void Rotate(float angle, glm::vec3 axis);
	void Scale(glm::vec3 scale);

private:
	glm::mat4 m_transform = glm::mat4(1);
};

