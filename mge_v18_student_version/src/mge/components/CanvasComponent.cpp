
#include "mge\core\GameObject.hpp"
#include "mge\core\World.hpp"
#include "mge\components\UISpriteRenderer.h"
#include "CanvasComponent.h"

CanvasComponent::CanvasComponent()
{

	//Used for custom shading
	/*
	m_canvasWidth = AbstractGame::Instance()->WindowWidth();
	m_canvasHeight = AbstractGame::Instance()->WindowHeight();
	m_projectionMat = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f,  -1.0f, 1.0f);

	m_projectionMat = glm::mat4(
		glm::vec4(1 / 960.0f, 0, 0, 0),
		glm::vec4(0, 1 / 540.0f, 0, 0),
		glm::vec4(0, 0, 1, 0),
		glm::vec4(-1, -1, 0, 1)
	);
	std::cout << m_projectionMat[0] << std::endl;
	*/
}

CanvasComponent::~CanvasComponent()
{

}

void CanvasComponent::AddSpriteRenderer(UISpriteRenderer * pUISpriteRenderer)
{
	m_uISpriteRenderers.push_back(pUISpriteRenderer);
}

void CanvasComponent::DrawAllUISprites(sf::RenderWindow* window)
{
	for (int i = m_uISpriteRenderers.size()-1; i >=0; i--)
	{
		m_uISpriteRenderers[i]->DrawSprite(window);
	}
}

void CanvasComponent::Awake()
{
	m_gameObject->GetWorld()->SetCanvas(this);
}
