#include "LightComponent.h"



LightComponent::LightComponent()
{
}


LightComponent::~LightComponent()
{
}


LightType LightComponent::GetType()
{
	return m_type;
}

glm::vec3 LightComponent::GetColor()
{
	return m_color;
}

glm::vec3 LightComponent::GetAmbient()
{
	return m_ambient;
}

float LightComponent::GetIntensity()
{
	return m_intensity;
}

float LightComponent::GetAmbientContribution()
{
	return m_ambientContribution;
}

float LightComponent::GetSpecularContribution()
{
	return m_specularContribution;
}

void LightComponent::SetType(LightType type)
{
	m_type = type;
}

void LightComponent::SetColor(glm::vec3 color)
{
	m_color = color;
}

void LightComponent::SetAmbient(glm::vec3 ambient)
{
	m_ambient = ambient;
}

void LightComponent::SetIntensity(float intensity)
{
	m_intensity = intensity;
}

void LightComponent::SetAmbientcontribution(float ambientContribution)
{
	m_ambientContribution = ambientContribution;
}

void LightComponent::SetSpecularContribution(float specularContribution)
{
	m_specularContribution = specularContribution;
}

void LightComponent::SetAttenuationConstants(glm::vec3 constants)
{
	m_attenuationConstants = constants;
}

void LightComponent::SetCutoffAngle(float angle)
{
	m_cutoffAngle = angle;
}

void LightComponent::SetOuterCutoffAngle(float angle)
{
	m_outerCutoffAngle = angle;
}

float LightComponent::GetCutoffAngle()
{
	return m_cutoffAngle;
}

float LightComponent::GetOuterCutoffAngle()
{
	return m_outerCutoffAngle;
}

glm::vec3 LightComponent::GetAttenuationConstants()
{
	return m_attenuationConstants;
}