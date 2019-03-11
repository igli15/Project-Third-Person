#pragma once
#include <SFML/Window.hpp>
#include <functional>

class KeyObject
{
public:
	//TODO: INITILIZE EMPTY FUNC
	std::function<void()> onKeyEnter;
	std::function<void()> onKeyStay;
	std::function<void()> onKeyExit;

	KeyObject(sf::Keyboard::Key key);
	~KeyObject();

	bool KeyPressed();

private:
	sf::Keyboard::Key m_key;
	bool m_isKeyPressedLastFrame = false;
};

