
#include "mge\core\GameObject.hpp"
#include "mge\core\World.hpp"
#include "mge\components\UISpriteRenderer.h"
#include "mge\components\TextComponent.h"
#include "CanvasComponent.h"
#include <vector>
#include <algorithm>

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

void CanvasComponent::AddTextComponent(TextComponent * textComponent)
{
	m_textComponents.push_back(textComponent);
}

void CanvasComponent::RemoveSpriteRenderer(UISpriteRenderer * pUISpriteRenderer)
{
	auto it = std::find(m_uISpriteRenderers.begin(), m_uISpriteRenderers.end(), pUISpriteRenderer);
	if (it != m_uISpriteRenderers.end())
	{
		m_uISpriteRenderers.erase(it);
	}
}

void CanvasComponent::RemoveTextComponent(TextComponent * textComponent)
{
	auto it = std::find(m_textComponents.begin(), m_textComponents.end(), textComponent);
	if (it != m_textComponents.end())
	{
		m_textComponents.erase(it);
	}
}

void CanvasComponent::DrawAllUISprites(sf::RenderWindow* window)
{
	for (int i = m_uISpriteRenderers.size()-1; i >=0; i--)
	{
		m_uISpriteRenderers[i]->DrawSprite(window);
	}
}

void CanvasComponent::DrawAllTexts(sf::RenderWindow * window)
{
	for (int i = m_textComponents.size() - 1; i >= 0; i--)
	{
		m_textComponents[i]->DrawText(window);
	}
}

void CanvasComponent::Awake()
{
	m_gameObject->GetWorld()->SetCanvas(this);
}
