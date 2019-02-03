#include "glm.hpp"

#include "ColorMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "../components/MeshRenderer.h"
#include "mge/core/Mesh.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/World.hpp"
#include "mge/components/LightComponent.h"
#include "mge/components/Transform.h"

ShaderProgram* ColorMaterial::m_shaderProgram = NULL;

ColorMaterial::ColorMaterial() 
{
	InitializeShader();
}


ColorMaterial::~ColorMaterial()
{
}

void ColorMaterial::render(World * pWorld, MeshRenderer* meshRenderer , const glm::mat4 & pModelMatrix, const glm::mat4 & pViewMatrix, const glm::mat4 & pProjectionMatrix)
{
	m_shaderProgram->use();

	int pointLightCount = 0;
	int spotLightCount = 0;
	int directionalLightCount = 0;

	for (int i = 0; i < pWorld->getLightCount(); i++)
	{
		if (pWorld->getLightAt(i)->GetType() == LightType::POINT)
		{
			pointLightCount += 1;
		}
		else if (pWorld->getLightAt(i)->GetType() == LightType::DIRECTIONAL)
		{
			directionalLightCount += 1;
		}
		else if (pWorld->getLightAt(i)->GetType() == LightType::SPOTLIGHT)
		{
			spotLightCount += 1;
		}
	}

	for (int i = 0; i < pWorld->getLightCount(); i++)
	{
		std::string pointLightstring = "pointLight[" + std::to_string(pointLightCount - 1) + "].";

		std::string dirLightstring = "directionalLight[" + std::to_string(directionalLightCount - 1) + "].";

		std::string spotLightstring = "spotLight[" + std::to_string(spotLightCount - 1) + "].";

		LightComponent* currentLight = pWorld->getLightAt(i);
		if (currentLight->GetType() == LightType::POINT)
		{
			//pointLightCount += 1;
			//std::cout << pointLightstring << std::endl;
			glUniform3fv(m_shaderProgram->getUniformLocation(pointLightstring + "lightColor"), 1, glm::value_ptr(currentLight->GetColor() * currentLight->GetIntensity()));
			glUniform3fv(m_shaderProgram->getUniformLocation(pointLightstring + "lightPos"), 1, glm::value_ptr(pViewMatrix * currentLight->GetGameObject()->transform->WorldTransform()[3]));
			glUniform1f(m_shaderProgram->getUniformLocation(pointLightstring + "ambientContribution"), currentLight->GetAmbientContribution());
			glUniform1f(m_shaderProgram->getUniformLocation(pointLightstring + "specularContribution"), currentLight->GetSpecularContribution());
		}
		else if (currentLight->GetType() == LightType::DIRECTIONAL)
		{
			//directionalLightCount += 1;
			glUniform3fv(m_shaderProgram->getUniformLocation(dirLightstring + "lightColor"), 1, glm::value_ptr(currentLight->GetColor() * currentLight->GetIntensity()));
			glUniform3fv(m_shaderProgram->getUniformLocation(dirLightstring + "direction"), 1, glm::value_ptr(currentLight->GetGameObject()->transform->LocalTransform()[2]));
			glUniform1f(m_shaderProgram->getUniformLocation(dirLightstring + "ambientContribution"), currentLight->GetAmbientContribution());
			glUniform1f(m_shaderProgram->getUniformLocation(dirLightstring + "specularContribution"), currentLight->GetSpecularContribution());
		}
		else if (currentLight->GetType() == LightType::SPOTLIGHT)
		{
			//spotLightCount += 1;
			glUniform3fv(m_shaderProgram->getUniformLocation(spotLightstring + "lightColor"), 1, glm::value_ptr(currentLight->GetColor() * currentLight->GetIntensity()));
			glUniform3fv(m_shaderProgram->getUniformLocation(spotLightstring + "lightPos"), 1, glm::value_ptr(pViewMatrix *currentLight->GetGameObject()->transform->WorldTransform()[3]));
			glUniform3fv(m_shaderProgram->getUniformLocation(spotLightstring + "direction"), 1, glm::value_ptr(currentLight->GetGameObject()->transform->LocalTransform()[2]));

			glUniform1f(m_shaderProgram->getUniformLocation(spotLightstring + "ambientContribution"), currentLight->GetAmbientContribution());
			glUniform1f(m_shaderProgram->getUniformLocation(spotLightstring + "specularContribution"), currentLight->GetSpecularContribution());

			glUniform1f(m_shaderProgram->getUniformLocation(spotLightstring + "cutoff"), glm::cos(glm::radians(currentLight->GetCutoffAngle())));
			glUniform1f(m_shaderProgram->getUniformLocation(spotLightstring + "outerCutoff"), glm::cos(glm::radians(currentLight->GetOuterCutoffAngle())));
		}

		glm::vec3 attenuationConstants = currentLight->GetAttenuationConstants();
		glUniform1f(m_shaderProgram->getUniformLocation(pointLightstring + "constant"), attenuationConstants.x);
		glUniform1f(m_shaderProgram->getUniformLocation(pointLightstring + "linear"), attenuationConstants.y);
		glUniform1f(m_shaderProgram->getUniformLocation(pointLightstring + "quadratic"), attenuationConstants.z);

		glUniform1f(m_shaderProgram->getUniformLocation(spotLightstring + "constant"), attenuationConstants.x);
		glUniform1f(m_shaderProgram->getUniformLocation(spotLightstring + "linear"), attenuationConstants.y);
		glUniform1f(m_shaderProgram->getUniformLocation(spotLightstring + "quadratic"), attenuationConstants.z);
	}

	//std::cout << pointLightCount << "  " << directionalLightCount << std::endl;
	glUniform1f(m_shaderProgram->getUniformLocation("pointLightCount"), pointLightCount);
	glUniform1f(m_shaderProgram->getUniformLocation("directionalLightCount"), directionalLightCount);
	glUniform1f(m_shaderProgram->getUniformLocation("spotLightCount"), spotLightCount);

	glUniform1f(m_shaderProgram->getUniformLocation("shineness"), m_shineness);
	glUniform3fv(m_shaderProgram->getUniformLocation("diffuseColor"), 1, glm::value_ptr(m_diffuseColor));
	glUniformMatrix4fv(m_shaderProgram->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(m_shaderProgram->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(m_shaderProgram->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));


	meshRenderer->StreamToOpenGL(
		m_shaderProgram->getAttribLocation("vertex"),
		m_shaderProgram->getAttribLocation("normal"),
		m_shaderProgram->getAttribLocation("uv")
	);

}

void ColorMaterial::InitializeShader()
{
	m_shaderProgram = new ShaderProgram();
	m_shaderProgram->use();
	m_shaderProgram->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "color.vs");
	m_shaderProgram->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "color.fs");
	m_shaderProgram->finalize();
}
