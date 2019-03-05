#include "TextComponent.h"
#include "mge\core\GameObject.hpp"
#include "mge/core/World.hpp"
#include "mge\components\CanvasComponent.h"
#include "mge\components\TextComponent.h"


TextComponent::TextComponent()
{
}


TextComponent::~TextComponent()
{
	m_font = nullptr;
	m_text = nullptr;
	delete m_text;
}

void TextComponent::DrawText(sf::RenderWindow * window)
{
	if (m_text != nullptr)
	{
		window->pushGLStates();
		window->draw(*m_text);
		window->popGLStates();
	}
}

void TextComponent::Awake()
{
	m_gameObject->GetWorld()->GetCanvasComponent()->AddTextComponent(this);
}

void TextComponent::OnDestroy()
{
	m_gameObject->GetWorld()->GetCanvasComponent()->RemoveTextComponent(this);
}

sf::Text* TextComponent::CreateText(sf::Font * font)
{
	if (m_text == nullptr)
	{
		m_font = font;
		m_text = new sf::Text();
		m_text->setFont(*m_font);
		return m_text;
	}
	else
	{
		delete m_text;
		m_font = font;
		m_text = new sf::Text();
		m_text->setFont(*m_font);
		return m_text;
	}
}
