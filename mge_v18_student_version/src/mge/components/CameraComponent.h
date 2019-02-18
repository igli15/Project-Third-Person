#pragma once
#include "glm.hpp"
#include "../core/Component.h"
#include "../core/XMLComponent.h"

class CameraComponent : public XMLComponent
{
public:
	CameraComponent();
	virtual ~CameraComponent();
	void Awake() override;

	glm::mat4& GetProjection();

	void SetFOV(float fov);
	void SetApsectRatio(float aspectRatio);
	void SetNearClipPlane(float nearClipPlane);
	void SetFarClipPlane(float farClipPlane);

	float GetFOV() const;
	float GetAspectRatio() const;
	float GetNearClipPlane() const;
	float GetFarCLipPlane() const;

	void Parse(rapidxml::xml_node<>* compNode) override;

private:
	float m_FOV = 60.0f;
	float m_aspectRatio = 4.0f/3.0f;
	float m_nearClipPlane = 0.1f;
	float m_farClipPlane = 1000.0f;

	glm::mat4 m_projection = glm::mat4(1); //just to initialize
};

