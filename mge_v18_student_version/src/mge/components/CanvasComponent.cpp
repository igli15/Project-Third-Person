
#include "mge\core\GameObject.hpp"
#include "mge\core\World.hpp"
#include "mge\components\UISpriteRenderer.h"
#include "CanvasComponent.h"

CanvasComponent::CanvasComponent()
{
	m_projectionMat = glm::ortho(0.0f, (float)m_canvasWidth, (float)m_canvasHeight, 0.0f, -1.0f, 1.0f);
}

CanvasComponent::~CanvasComponent()
{

}

void CanvasComponent::AddSpriteRenderer(UISpriteRenderer * pUISpriteRenderer)
{
	m_uISpriteRenderers.push_back(pUISpriteRenderer);
}

void CanvasComponent::DrawAllUISprites()
{
	for (int i = m_uISpriteRenderers.size()-1; i >=0; i--)
	{
		m_uISpriteRenderers[i]->DrawSprite(m_projectionMat);
	}
}

void CanvasComponent::Awake()
{
	m_gameObject->GetWorld()->SetCanvas(this);

	m_canvasWidth = AbstractGame::Instance()->WindowWidth();
	m_canvasHeight = AbstractGame::Instance()->WindowHeight();
}
