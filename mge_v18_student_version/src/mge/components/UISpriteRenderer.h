#pragma once
#include <SFML\Graphics.hpp>
#include "mge\core\AbstractGame.hpp"
#include "mge\core\Component.h"

class CanvasComponent;

class UISpriteRenderer : public Component
{
public:
	UISpriteRenderer();
	virtual ~UISpriteRenderer();
	sf::Sprite* ApplyTextureToSprite(sf::Texture* pTexture);
	void DrawSprite();
	void Awake() override;
private:
	sf::Texture* m_texture = nullptr;
	sf::Sprite* m_sprite = nullptr;
};

