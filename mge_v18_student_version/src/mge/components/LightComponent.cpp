#include "LightComponent.h"
#include "mge/core/GameObject.hpp"
#include "mge/core/World.hpp"

LightComponent::LightComponent()
{
	
}


LightComponent::~LightComponent()
{
	m_gameObject->GetWorld()->unregisterLight(this);
}

void LightComponent::Awake()
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

void LightComponent::Parse(rapidxml::xml_node<>* compNode)
{
	for (rapidxml::xml_attribute<>* a = compNode->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
		std::string attributeName = a->name();
		if (attributeName == "type")
		{
			std::string value(a->value());
			if (value == "DIRECTIONAL")
			{
				m_type = LightType::DIRECTIONAL;
			}
			else if (value == "POINT")
			{
				m_type = LightType::POINT;
			}
			else if (value == "SPOTLIGHT")
			{
				m_type = LightType::SPOTLIGHT;
			}
		}
		else if (attributeName == "color")
		{
			glm::vec3 color;
			sscanf(a->value(), "(%f,%f,%f)", &color.x, &color.y, &color.z);
			SetColor(color);
		}
		else if (attributeName == "ambientColor")
		{
			glm::vec3 color;
			sscanf(a->value(), "(%f,%f,%f)", &color.x, &color.y, &color.z);
			SetColor(color);
		}
		else if (attributeName == "outercutoffAngle")
		{
			SetOuterCutoffAngle(strtof(a->value(), 0));
		}
		else if (attributeName == "intensity")	
		{
			SetIntensity(strtof(a->value(), 0));
		}
		else if (attributeName == "ambientContribution")
		{
			SetAmbientcontribution(strtof(a->value(), 0));
		}
		else if (attributeName == "specularContribution")
		{
			SetSpecularContribution(strtof(a->value(), 0));
		}
		else if (attributeName == "attenuationConstants")
		{
			glm::vec3 consts;
			sscanf(a->value(), "(%f,%f,%f)", &consts.x, &consts.y, &consts.z);
			SetAttenuationConstants(consts);
		}
		else if (attributeName == "cutoffAngle")
		{
			SetCutoffAngle(strtof(a->value(), 0));
		}
		else if (attributeName == "outercutoffAngle")
		{
			SetOuterCutoffAngle(strtof(a->value(), 0));
		}

	}
}
