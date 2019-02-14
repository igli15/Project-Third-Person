
#include "mge\core\GameObject.hpp"
#include "mge\core\World.hpp"
#include "mge\components\UISpriteRenderer.h"
#include "CanvasComponent.h"

CanvasComponent::CanvasComponent()
{
	
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
		m_uISpriteRenderers[i]->DrawSprite();
	}
}

void CanvasComponent::Awake()
{
	m_gameObject->GetWorld()->SetCanvas(this);
}
