#include "glm.hpp"

#include "TextureMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"
#include "../components/MeshRenderer.h"
#include "../components/LightComponent.h"
#include "mge/core/ResourceManager.h"

ShaderProgram* TextureMaterial::m_shaderProgram = NULL;

GLint TextureMaterial::_uMVPMatrix = 0;
GLint TextureMaterial::_uDiffuseTexture = 0;

GLint TextureMaterial::_aVertex = 0;
GLint TextureMaterial::_aNormal = 0;
GLint TextureMaterial::_aUV = 0;

TextureMaterial::TextureMaterial(Texture * pDiffuseTexture , Texture* specularTexture = nullptr, Texture* emissionTexture = nullptr)
	:_diffuseTexture(pDiffuseTexture),m_spcecularTexture(specularTexture),m_emissionTexture(emissionTexture)
{
    _lazyInitializeShader();
 
	m_whiteTex = AbstractGame::Instance()->GetResourceManager()->GetTexture("whiteTex");
	m_blackTex = AbstractGame::Instance()->GetResourceManager()->GetTexture("blackTex");
}

TextureMaterial::~TextureMaterial() {}

void TextureMaterial::_lazyInitializeShader() {
    if (!m_shaderProgram) {
        m_shaderProgram = new ShaderProgram();
        m_shaderProgram->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"texture.vs");
        m_shaderProgram->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"texture.fs");
        m_shaderProgram->finalize();

        //cache all the uniform and attribute indexes
        _uDiffuseTexture = m_shaderProgram->getUniformLocation("diffuseTexture");

        _aVertex = m_shaderProgram->getAttribLocation("vertex");
        _aNormal = m_shaderProgram->getAttribLocation("normal");
        _aUV =     m_shaderProgram->getAttribLocation("uv");
    }
}

void TextureMaterial::setDiffuseTexture (Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void TextureMaterial::SetSpecularTexture(Texture * specularTexture)
{
	m_spcecularTexture = specularTexture;
}

void TextureMaterial::SetDiffuseColor(glm::vec3 color)
{
	m_diffuseColor = color;
}

void TextureMaterial::SetShininess(float shininess)
{
	m_shineness;
}

void TextureMaterial::render(World* pWorld, MeshRenderer* meshRenderer, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    if (!_diffuseTexture) return;

    m_shaderProgram->use();

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
	//tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(_uDiffuseTexture, 0);

	if (m_spcecularTexture != nullptr)
	{
		//setup texture slot 1
		glActiveTexture(GL_TEXTURE1);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, m_spcecularTexture->getId());
		//tell the shader the texture slot for the specular texture is slot 1
		glUniform1i(m_shaderProgram->getUniformLocation("specularTexture"), 1);
	}
	else
	{
		//setup texture slot 1
		glActiveTexture(GL_TEXTURE1);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, m_whiteTex->getId());
		//tell the shader the texture slot for the specular texture is slot 1
		glUniform1i(m_shaderProgram->getUniformLocation("specularTexture"), 1);
	}

	if (m_emissionTexture != nullptr)
	{
		//setup texture slot 2
		glActiveTexture(GL_TEXTURE2);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, m_emissionTexture->getId());
		//tell the shader the texture slot for the specular texture is slot 2
		glUniform1i(m_shaderProgram->getUniformLocation("emissionTexture"), 2);
	}
	else
	{
		//setup texture slot 2
		glActiveTexture(GL_TEXTURE2);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, m_blackTex->getId());
		//tell the shader the texture slot for the specular texture is slot 2
		glUniform1i(m_shaderProgram->getUniformLocation("emissionTexture"), 2);
	}

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
			//std::cout << spotLightstring << std::endl;
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


    //Print the number of lights in the scene and the position of the first light.
    //It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
    //if (pWorld->getLightCount() > 0) {
    //    std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
    //}


	glUniformMatrix4fv(m_shaderProgram->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(m_shaderProgram->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(m_shaderProgram->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));

    //now inform mesh of where to stream its data
    meshRenderer->StreamToOpenGL(_aVertex, _aNormal, _aUV);
}
