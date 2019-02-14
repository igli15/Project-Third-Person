#include "UISpriteRenderer.h"
#include <SFML\Graphics.hpp>
#include "mge\core\AbstractGame.hpp"
#include "mge\components\CanvasComponent.h"
#include "mge\core\GameObject.hpp"
#include "mge\core\World.hpp"
#include "mge/config.hpp"

ShaderProgram* UISpriteRenderer::m_shaderProgram = nullptr;

UISpriteRenderer::UISpriteRenderer()
{
	
}


UISpriteRenderer::~UISpriteRenderer()
{
	m_texture = nullptr;
}


void UISpriteRenderer::DrawSprite(glm::mat4 projection)
{
	//AbstractGame::Instance()->GetWindow()->draw(*m_sprite);
	m_shaderProgram->use();
	glm::mat4 model;


	glm::vec3 pos = m_gameObject->transform->WorldPosition();
	pos.z = 0;
	glm::translate(model,pos);

	model = glm::translate(model, glm::vec3(0.5f * m_texture->Image()->getSize().x, 0.5f * m_texture->Image()->getSize().y, 0.0f));
	//rotate here
	model = glm::translate(model, glm::vec3(-0.5f * m_texture->Image()->getSize().x, -0.5f * m_texture->Image()->getSize().y, 0.0f));

	glUniformMatrix4fv(m_shaderProgram->getUniformLocation("model"),1,GL_FALSE,glm::value_ptr(model));
	glUniformMatrix4fv(m_shaderProgram->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniform3fv(m_shaderProgram->getUniformLocation("spriteColor"), 1, glm::value_ptr(m_tintColor));

	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, m_texture->getId());
	//tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(m_shaderProgram->getUniformLocation("image"), 0);

	glBindVertexArray(this->m_quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void UISpriteRenderer::InitRenderingQuad()
{
	GLuint VBO;
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->m_quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->m_quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void UISpriteRenderer::Awake()
{
	InitShaderProgram();
	InitRenderingQuad();
	m_gameObject->GetWorld()->GetCanvasComponent()->AddSpriteRenderer(this);
}

void UISpriteRenderer::SetTexture(Texture * tex)
{
	m_texture = tex;
}

void UISpriteRenderer::SetTintColor(glm::vec3 tint)
{
	m_tintColor = tint;
}

void UISpriteRenderer::InitShaderProgram()
{
	m_shaderProgram = new ShaderProgram();
	m_shaderProgram->use();
	m_shaderProgram->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "uisprite.vs");
	m_shaderProgram->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "uisprite.fs");
	m_shaderProgram->finalize();
}


