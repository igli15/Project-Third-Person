#include "KeyObject.h"
#include <iostream>

KeyObject::KeyObject(sf::Keyboard::Key key)
{
	m_key = key;
}


KeyObject::~KeyObject()
{
}

void KeyObject::KeyPressed()
{
	bool isPressed = sf::Keyboard::isKeyPressed(m_key);

	if (!m_isKeyPressedLastFrame&&isPressed)
	{
		//OnKeyEnter
		if(onKeyEnter!=NULL) onKeyEnter();
	}
	if (m_isKeyPressedLastFrame&&isPressed)
	{
		//OnKeyStay
		if (onKeyStay != NULL) onKeyStay();
	}
	if (m_isKeyPressedLastFrame && !isPressed)
	{
		//OnKeyExit
		if (onKeyExit != NULL) onKeyExit();
	}
	m_isKeyPressedLastFrame = isPressed;
}
