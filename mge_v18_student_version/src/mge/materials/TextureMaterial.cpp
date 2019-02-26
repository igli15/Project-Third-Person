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

GLint TextureMaterial::m_uSpecularTexture = 0;
GLint TextureMaterial::m_uEmissionTexture = 0;
GLint TextureMaterial::m_uNormalTexture = 0;

GLint TextureMaterial::m_uPointLightCount = 0;
GLint TextureMaterial::m_uSpotLightCount = 0;
GLint TextureMaterial::m_uDirectionalLightCount = 0;

GLint TextureMaterial::m_uShineness = 0;
GLint TextureMaterial::m_uEmissionScale = 0;
GLint TextureMaterial::m_uDiffuseColor = 0;

GLint TextureMaterial::m_uProjectionMatrix = 0;
GLint TextureMaterial::m_uViewMatrix = 0;
GLint TextureMaterial::m_uModelMatrix = 0;

GLint TextureMaterial::m_aTangent = 0;
GLint TextureMaterial::m_aBiTangent = 0;

TextureMaterial::TextureMaterial(Texture * pDiffuseTexture , Texture* specularTexture , Texture* emissionTexture,Texture* normalTex)
	:_diffuseTexture(pDiffuseTexture),m_spcecularTexture(specularTexture),m_emissionTexture(emissionTexture)
{
	m_normalMap = normalTex;
	
 
	m_whiteTex = AbstractGame::Instance()->GetResourceManager()->GetTexture("whiteTex");
	m_blackTex = AbstractGame::Instance()->GetResourceManager()->GetTexture("blackTex");
	m_normalFlatTex = AbstractGame::Instance()->GetResourceManager()->GetTexture("flatNormalTex");

	_lazyInitializeShader();
}

TextureMaterial::~TextureMaterial() {}

void TextureMaterial::_lazyInitializeShader() {
    if (!m_shaderProgram) 
	{
        m_shaderProgram = new ShaderProgram();

		m_shaderProgram->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "textureNormal.vs");
		m_shaderProgram->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "textureNormal.fs");
		m_shaderProgram->finalize();

        //cache all the uniform and attribute indexes
        _uDiffuseTexture = m_shaderProgram->getUniformLocation("diffuseTexture");

        _aVertex = m_shaderProgram->getAttribLocation("vertex");
        _aNormal = m_shaderProgram->getAttribLocation("normal");
        _aUV =     m_shaderProgram->getAttribLocation("uv");

		m_aTangent = m_shaderProgram->getAttribLocation("tangent");
		m_aBiTangent = m_shaderProgram->getAttribLocation("bitangent");

		m_uSpecularTexture = m_shaderProgram->getUniformLocation("specularTexture");
		m_uEmissionTexture = m_shaderProgram->getUniformLocation("emissionTexture");
		m_uNormalTexture = m_shaderProgram->getUniformLocation("normalMap");

		m_uDirectionalLightCount = m_shaderProgram->getUniformLocation("directionalLightCount");
		m_uPointLightCount = m_shaderProgram->getUniformLocation("pointLightCount");
		m_uSpotLightCount = m_shaderProgram->getUniformLocation("spotLightCount");

		m_uShineness = m_shaderProgram->getUniformLocation("shineness");
		m_uEmissionScale = m_shaderProgram->getUniformLocation("emissionScale");
		m_uDiffuseColor = m_shaderProgram->getUniformLocation("diffuseColor");

		m_uModelMatrix = m_shaderProgram->getUniformLocation("modelMatrix");
		m_uProjectionMatrix = m_shaderProgram->getUniformLocation("projectionMatrix");
		m_uViewMatrix = m_shaderProgram->getUniformLocation("viewMatrix");
    }
}

void TextureMaterial::setDiffuseTexture (Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void TextureMaterial::SetSpecularTexture(Texture * specularTexture)
{
	m_spcecularTexture = specularTexture;
}

void TextureMaterial::SetEmissionTexture(Texture * emissionTexture)
{
	m_emissionTexture = emissionTexture;
}

void TextureMaterial::SetNormalTexture(Texture * normalTexture)
{
	m_normalMap = normalTexture;
}

void TextureMaterial::SetDiffuseColor(glm::vec3 color)
{
	m_diffuseColor = color;
}

void TextureMaterial::SetShininess(float shininess)
{
	m_shineness;
}

void TextureMaterial::SetEmissionScale(float emissionScale)
{
	m_emissionScale = emissionScale;
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
		//glUniform1i(m_shaderProgram->getUniformLocation("specularTexture"), 1);
		glUniform1i(m_uSpecularTexture, 1);
	}
	else
	{
		//setup texture slot 1
		glActiveTexture(GL_TEXTURE1);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, m_whiteTex->getId());
		//tell the shader the texture slot for the specular texture is slot 1
		glUniform1i(m_uSpecularTexture, 1);
	}

	if (m_emissionTexture != nullptr)
	{
		//setup texture slot 2
		glActiveTexture(GL_TEXTURE2);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, m_emissionTexture->getId());
		//tell the shader the texture slot for the specular texture is slot 2
		//glUniform1i(m_shaderProgram->getUniformLocation("emissionTexture"), 2);
		glUniform1i(m_uEmissionTexture, 2);
	}
	else
	{
		//setup texture slot 2
		glActiveTexture(GL_TEXTURE2);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, m_blackTex->getId());
		//tell the shader the texture slot for the specular texture is slot 2
		glUniform1i(m_uEmissionTexture, 2);
	}

	
	if (m_normalMap != nullptr)
	{
		//setup texture slot 3
		glActiveTexture(GL_TEXTURE3);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, m_normalMap->getId());
		//tell the shader the texture slot for the specular texture is slot 3
		//glUniform1i(m_shaderProgram->getUniformLocation("normalMap"), 3);
		glUniform1i(m_uNormalTexture, 3);
	}
	else
	{
		//setup texture slot 3
		glActiveTexture(GL_TEXTURE3);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, m_normalFlatTex->getId());
		//tell the shader the texture slot for the specular texture is slot 3
		glUniform1i(m_uNormalTexture, 3);
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
		

		//pointLightstring = "pointLight[" + std::to_string(pointLightCount - 1) + "].";

		//dirLightstring = "directionalLight[" + std::to_string(directionalLightCount - 1) + "].";

		//spotLightstring = "spotLight[" + std::to_string(spotLightCount - 1) + "].";

		

		LightComponent* currentLight = pWorld->getLightAt(i);

		if (currentLight->GetType() == LightType::POINT)
		{
			//pointLightCount += 1;
			//std::cout << pointLightstring << std::endl;
			glUniform3fv(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "lightColor"), 1, glm::value_ptr(currentLight->GetColor() * currentLight->GetIntensity()));
			glUniform3fv(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "lightPos"), 1, glm::value_ptr(pViewMatrix * currentLight->GetGameObject()->transform->WorldTransform()[3]));
			glUniform1f(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "ambientContribution"), currentLight->GetAmbientContribution());
			glUniform1f(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "specularContribution"), currentLight->GetSpecularContribution());
		}
		else if (currentLight->GetType() == LightType::DIRECTIONAL)
		{
			//directionalLightCount += 1;
		
			glUniform3fv(currentLight->uLightColor, 1, glm::value_ptr(currentLight->GetColor() * currentLight->GetIntensity()));
			//glUniform3fv(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "direction"), 1, glm::value_ptr(currentLight->GetGameObject()->transform->LocalTransform()[2]));
			glUniform3fv(currentLight->uDirection, 1, glm::value_ptr(currentLight->GetGameObject()->transform->LocalTransform()[2]));
			//glUniform1f(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "ambientContribution"), currentLight->GetAmbientContribution());
			glUniform1f(currentLight->uAmbientContribution, currentLight->GetAmbientContribution());
			//glUniform1f(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "specularContribution"), currentLight->GetSpecularContribution());
			glUniform1f(currentLight->uSpecularContribution, currentLight->GetSpecularContribution());
		}
		else if (currentLight->GetType() == LightType::SPOTLIGHT)
		{
			//spotLightCount += 1;
			//std::cout << spotLightstring << std::endl;
			glUniform3fv(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "lightColor"), 1, glm::value_ptr(currentLight->GetColor() * currentLight->GetIntensity()));
			glUniform3fv(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "lightPos"), 1, glm::value_ptr(pViewMatrix *currentLight->GetGameObject()->transform->WorldTransform()[3]));
			glUniform3fv(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "direction"), 1, glm::value_ptr(currentLight->GetGameObject()->transform->LocalTransform()[2]));

			glUniform1f(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "ambientContribution"), currentLight->GetAmbientContribution());
			glUniform1f(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "specularContribution"), currentLight->GetSpecularContribution());

			glUniform1f(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "cutoff"), glm::cos(glm::radians(currentLight->GetCutoffAngle())));
			glUniform1f(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "outerCutoff"), glm::cos(glm::radians(currentLight->GetOuterCutoffAngle())));
		}

		
		glm::vec3 attenuationConstants = currentLight->GetAttenuationConstants();
		/*
		glUniform1f(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "constant"), attenuationConstants.x);
		glUniform1f(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "linear"), attenuationConstants.y);
		glUniform1f(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "quadratic"), attenuationConstants.z);

		glUniform1f(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "constant"), attenuationConstants.x);
		glUniform1f(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "linear"), attenuationConstants.y);
		glUniform1f(m_shaderProgram->getUniformLocation(pWorld->getLightAt(i)->GetMaterialIndexString() + "quadratic"), attenuationConstants.z);
		*/

		glUniform1f(currentLight->uConstant, attenuationConstants.x);
		glUniform1f(currentLight->uLinear, attenuationConstants.y);
		glUniform1f(currentLight->uQuadratic, attenuationConstants.z);
	}

	//std::cout << pointLightCount << "  " << directionalLightCount << std::endl;
	/*
	glUniform1f(m_shaderProgram->getUniformLocation("pointLightCount"), pointLightCount);
	glUniform1f(m_shaderProgram->getUniformLocation("directionalLightCount"), directionalLightCount);
	glUniform1f(m_shaderProgram->getUniformLocation("spotLightCount"), spotLightCount);
	*/
	glUniform1f(m_uPointLightCount, pointLightCount);
	glUniform1f(m_uDirectionalLightCount, directionalLightCount);
	glUniform1f(m_uSpotLightCount, spotLightCount);

	/*
	glUniform1f(m_shaderProgram->getUniformLocation("shineness"), m_shineness);
	glUniform1f(m_shaderProgram->getUniformLocation("emissionScale"), m_emissionScale);
	glUniform3fv(m_shaderProgram->getUniformLocation("diffuseColor"), 1, glm::value_ptr(m_diffuseColor));
	*/

	glUniform1f(m_uShineness, m_shineness);
	glUniform1f(m_uEmissionScale, m_emissionScale);
	glUniform3fv(m_uDiffuseColor, 1, glm::value_ptr(m_diffuseColor));

	/*
	glUniformMatrix4fv(m_shaderProgram->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(m_shaderProgram->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(m_shaderProgram->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));
	*/

	glUniformMatrix4fv(m_uProjectionMatrix, 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(m_uViewMatrix, 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(m_uModelMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix));

    //now inform mesh of where to stream its data
    meshRenderer->StreamToOpenGL(_aVertex, _aNormal, _aUV, m_aTangent, m_aBiTangent);
}
