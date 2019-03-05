#pragma once

#include <SFML/Graphics.hpp>
#include "mge\core\GameObject.hpp"
#include <SFML\Window.hpp>
#include "mge\core\Component.h"

class TextComponent : public Component
{
public:
	TextComponent();
	virtual ~TextComponent();


	void DrawText(sf::RenderWindow* window);

	void Awake() override;


	void OnDestroy() override;

	sf::Text* CreateText(sf::Font* texture);
private:
	sf::Font* m_font = nullptr;
	sf::Text * m_text = nullptr;
};

