#include "MenuUI.h"
#include "mge\core\AbstractGame.hpp"
#include "mge\components\CanvasComponent.h"
#include "mge\core\GameObject.hpp"
#include "mge\components\UISpriteRenderer.h"
#include "mge\core\ResourceManager.h"
#include <SFML\System.hpp>
#include "MainWorld.h"
#include "mge/core/WorldManager.h"

MenuUI::MenuUI()
{
}


MenuUI::~MenuUI()
{
}

void MenuUI::Load()
{
	std::cout << "show playGame Selected Sprite" << std::endl;

	m_menuBGTexture = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("menuBG");
	m_playSelectedTexture = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("playSelected");
	m_controlsSelectedTexture = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("controlsSelected");
	m_exitGameSelectedTexture = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("exitSelected");
	m_ControlScreenPressed = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("controlsScreenPressed");
	m_ControlScreen = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("controlsScreen");

	m_menuBGSprite = AddComponent<UISpriteRenderer>();
	m_menuBGSprite->ApplyTexture(m_menuBGTexture);
	GameObject::Load();


}

void MenuUI::Awake()
{
	GameObject::Awake();
	m_Selected = NONE;
}

void MenuUI::Start()
{
	GameObject::Start();
}

void MenuUI::Update(float pStep)
{
	GameObject::Update(pStep);
	m_pressCD -= 0.055f;
	if (!m_controlsLocked)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) | sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_Selected = PlayGame;
			std::cout << "show playGame Selected Sprite" << std::endl;

			m_menuBGSprite->ApplyTexture(m_playSelectedTexture);

		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) | sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_Selected = Controls;
			//show Controls Selected Sprite
			std::cout << "show Controls Selected Sprite" << std::endl;
			m_menuBGSprite->ApplyTexture(m_controlsSelectedTexture);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) | sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_Selected = ExitGame;
			//show Exit selected sprite
			std::cout << "show Exit selected sprite" << std::endl;
			m_menuBGSprite->ApplyTexture(m_exitGameSelectedTexture);

		}

		OnHoldControls();
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) | sf::Keyboard::isKeyPressed(sf::Keyboard::W) | sf::Keyboard::isKeyPressed(sf::Keyboard::Left) | sf::Keyboard::isKeyPressed(sf::Keyboard::A) | sf::Keyboard::isKeyPressed(sf::Keyboard::Right) | sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_menuBGSprite->ApplyTexture(m_ControlScreenPressed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) | sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) | sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			if (m_pressCD <= 0)
			{
				m_menuBGSprite->ApplyTexture(m_controlsSelectedTexture);
				m_Selected = Controls;
				m_controlsLocked = false;
				m_pressCD = 1.5f;
			}
		}
	}
	
}

void MenuUI::OnDestroy()
{
}

void MenuUI::OnHoldControls()
{
	if (m_pressCD <= 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) | sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		{
			switch (m_Selected)
			{
			case PlayGame:
				//Start Level 1
				m_pressCD = 1.5f;
				AbstractGame::Instance()->GetWorldManager()->CreateWorld<MainWorld>("MainWorld");
				break;
			case Controls:
				m_controlsLocked = true;
				m_pressCD = 1.5f;
				m_menuBGSprite->ApplyTexture(m_ControlScreenPressed);
				break;
			case ExitGame:
				std::exit(0);
				m_pressCD = 1.5f;
				break;
			default:
				std::cout << m_Selected << std::endl;
				m_pressCD = 1.5f;

				break;
			}
		}
	}
}
