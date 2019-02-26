#pragma once

#include "../src/mge/core/XMLComponent.h"

#include "glm.hpp"
#include <string>
#include "rapidxml/rapidxml.hpp"
#include "GL/glew.h"

enum LightType
{
	DIRECTIONAL,
	POINT,
	SPOTLIGHT
};

class LightComponent : public XMLComponent

{
public:

	LightComponent();
	virtual ~LightComponent();
	void Awake() override;
	LightType GetType();
	glm::vec3 GetColor();
	glm::vec3 GetAmbient();
	float GetIntensity();
	float GetAmbientContribution();
	float GetSpecularContribution();

	void SetType(LightType type);
	void SetColor(glm::vec3 color);
	void SetAmbient(glm::vec3 ambient);
	void SetIntensity(float intensity);
	void SetAmbientcontribution(float ambientContribution);
	void SetSpecularContribution(float specularContribution);

	void SetAttenuationConstants(glm::vec3 constants);
	void SetCutoffAngle(float angle);
	void SetOuterCutoffAngle(float angle);

	float GetCutoffAngle();
	float GetOuterCutoffAngle();
	glm::vec3 GetAttenuationConstants();

	void Parse(rapidxml::xml_node<>* compNode) override;

	std::string GetMaterialIndexString() const;
	void SetMaterialIndexString(const std::string& indexString);

	GLint uLightColor = 0;
	GLint uLightPos = 0;
	GLint uAmbientContribution = 0;
	GLint uSpecularContribution = 0;
	GLint uDirection = 0;
	GLint uCutoff = 0;
	GLint uOuterCutoff = 0;
	GLint uConstant = 0;
	GLint uLinear = 0;
	GLint uQuadratic = 0;

	void AssignUnifromLocation();

private:

	LightType m_type = LightType::DIRECTIONAL;
	glm::vec3 m_color = glm::vec3(1, 1, 1);
	glm::vec3 m_ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	float m_intensity = 1;
	float m_ambientContribution = 1;
	float m_specularContribution = 32;
	float m_cutoffAngle = 10;
	float m_outerCutoffAngle = 45;
	glm::vec3 m_attenuationConstants = glm::vec3(1,1,0);


	//use this for buffering light data in open gl as a uniform string!
	std::string m_materialIndexString;

};

