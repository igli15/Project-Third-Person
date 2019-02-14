#include "UISpriteRenderer.h"
#include <SFML\Graphics.hpp>
#include "mge\core\AbstractGame.hpp"
#include "mge\components\CanvasComponent.h"
#include "mge\core\GameObject.hpp"
#include "mge\core\World.hpp"

UISpriteRenderer::UISpriteRenderer()
{
	
}


UISpriteRenderer::~UISpriteRenderer()
{
	m_texture = nullptr;
	m_sprite = nullptr;
}

sf::Sprite* UISpriteRenderer::ApplyTextureToSprite(sf::Texture* pTexture)
{
	if (m_sprite == nullptr)
	{
		m_texture = pTexture;
		m_sprite = new sf::Sprite();
		m_sprite->setTexture(*m_texture);
		//we might wanna check /apply here for parent position
		return m_sprite;
	}
	else
	{
		m_texture = pTexture;
		m_sprite = new sf::Sprite();
		m_sprite->setTexture(*m_texture);
		return m_sprite;
	}
}

void UISpriteRenderer::DrawSprite()
{
	AbstractGame::Instance()->GetWindow()->draw(*m_sprite);
}

void UISpriteRenderer::Awake()
{
	m_gameObject->GetWorld()->GetCanvasComponent()->AddSpriteRenderer(this);
}


