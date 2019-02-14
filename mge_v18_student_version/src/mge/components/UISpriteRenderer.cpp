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


void UISpriteRenderer::DrawSprite()
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

void UISpriteRenderer::InitShaderProgram()
{
	m_shaderProgram = new ShaderProgram();
	m_shaderProgram->use();
	m_shaderProgram->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "uisprite.vs");
	m_shaderProgram->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "uisprite.fs");
	m_shaderProgram->finalize();
}


