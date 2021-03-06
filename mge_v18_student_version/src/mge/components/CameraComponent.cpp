#include "CameraComponent.h"



CameraComponent::CameraComponent()
{
	m_projection = glm::perspective(glm::radians(m_FOV), m_aspectRatio, m_nearClipPlane, m_farClipPlane);
}


CameraComponent::~CameraComponent()
{
}

void CameraComponent::Awake()
{
	
}

glm::mat4 & CameraComponent::GetProjection()
{
	return m_projection;
}

void CameraComponent::SetFOV(float fov)
{
	m_FOV = fov;
	m_projection = glm::perspective(glm::radians(m_FOV), m_aspectRatio, m_nearClipPlane, m_farClipPlane);
}

void CameraComponent::SetApsectRatio(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_projection = glm::perspective(glm::radians(m_FOV), m_aspectRatio, m_nearClipPlane, m_farClipPlane);
}

void CameraComponent::SetNearClipPlane(float nearClipPlane)
{
	m_nearClipPlane = nearClipPlane;
	m_projection = glm::perspective(glm::radians(m_FOV), m_aspectRatio, m_nearClipPlane, m_farClipPlane);
}

void CameraComponent::SetFarClipPlane(float farClipPlane)
{
	m_farClipPlane = farClipPlane;
	m_projection = glm::perspective(glm::radians(m_FOV), m_aspectRatio, m_nearClipPlane, m_farClipPlane);
}

float CameraComponent::GetFOV() const
{
	return m_FOV;
}

float CameraComponent::GetAspectRatio() const
{
	return m_aspectRatio;
}

float CameraComponent::GetNearClipPlane() const
{
	return m_nearClipPlane;
}

float CameraComponent::GetFarCLipPlane() const
{
	return m_farClipPlane;
}

void CameraComponent::Parse(rapidxml::xml_node<>* compNode)
{
	for (rapidxml::xml_attribute<>* a = compNode->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
		std::string attributeName = a->name();
		if (attributeName == "FOV")
		{
			SetFOV(strtof(a->value(),0));
		}
		else if (attributeName == "aspectRatio")
		{
			SetApsectRatio(strtof(a->value(), 0));
		}
		else if (attributeName == "nearClipPlane")
		{
			SetNearClipPlane(strtof(a->value(), 0));
		}
		else if (attributeName == "farClipPlane")
		{
			SetFarClipPlane(strtof(a->value(), 0));
		}
	}
}
