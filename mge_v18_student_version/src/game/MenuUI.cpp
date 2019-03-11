#include "MenuUI.h"
#include "mge\core\AbstractGame.hpp"
#include "mge\components\CanvasComponent.h"
#include "mge\core\GameObject.hpp"
#include "mge\components\UISpriteRenderer.h"
#include "mge\core\ResourceManager.h"
#include <SFML\System.hpp>
#include "MainWorld.h"
#include "mge/core/WorldManager.h"
#include "mge/core/PlayerPrefs.h"
#include "mge/components/AudioSource.h"
#include "ResolutionScreen.h"

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

	m_levelSelectedNone = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("levelSelectedNone");
	m_levelSelected1 = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("levelSelected1");
	m_levelSelected2 = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("levelSelected2");
	m_levelSelectedBack = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("levelSelectedBack");

	m_menuBGSprite = AddComponent<UISpriteRenderer>();
	m_menuBGSprite->ApplyTexture(m_menuBGTexture);

	m_menuMusicSF = AbstractGame::Instance()->GetResourceManager()->GetMusic("menuMusic");
	m_menuMusic = AddComponent<AudioSource>();
	m_menuMusic->SetMusic(m_menuMusicSF);

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
	bool m_controlsLocked = false;
	bool m_levelSelect = false;
	float m_pressCD = 1.5f;

	m_menuMusic->PlayMusic();
}

void MenuUI::Update(float pStep)
{
	GameObject::Update(pStep);
	m_pressCD -= 0.055f;

	if (!m_levelSelect)
	{
		if (!m_controlsLocked)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) | sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if (m_Selected != PlayGame)
				{
				//	m_selectingButton->PlayOneShotSound("selectingButton");
					m_menuBGSprite->ApplyTexture(m_playSelectedTexture);
				}
				m_Selected = PlayGame;
				std::cout << "show playGame Selected Sprite" << std::endl;
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) | sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				if (m_Selected != Controls)
				{
					//m_selectingButton->PlayOneShotSound("selectingButton");
					m_menuBGSprite->ApplyTexture(m_controlsSelectedTexture);
				}
				m_Selected = Controls;
				//show Controls Selected Sprite
				std::cout << "show Controls Selected Sprite" << std::endl;
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) | sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				if (m_Selected != ExitGame)
				{
					//m_selectingButton->PlayOneShotSound("selectingButton");
					m_menuBGSprite->ApplyTexture(m_exitGameSelectedTexture);	
				}
				m_Selected = ExitGame;
				//show Exit selected sprite
				std::cout << "show Exit selected sprite" << std::endl;

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
	else { 
		OnLevelSelect();
		OnHoldControls();
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
			m_pressingButton->PlayOneShotSound("pressingButton");
			switch (m_Selected)
			{
			case PlayGame:
				//Start Level 1
				m_pressCD = 1.5f;
				m_levelSelect = true;
				m_menuBGSprite->ApplyTexture(m_levelSelectedNone);
				//AbstractGame::Instance()->GetWorldManager()->CreateWorld<MainWorld>("MainWorld");
				break;
			case Controls:
				m_controlsLocked = true;
				m_pressCD = 1.5f;
				m_menuBGSprite->ApplyTexture(m_ControlScreenPressed);
				break;
			case ExitGame:
				m_pressCD = 1.5f;
				std::exit(0);
				break;
			case Level1:
				PlayerPrefs::SetInt("LevelIndex", 1);
				m_menuMusic->StopMusic();
				AbstractGame::Instance()->GetWorldManager()->CreateWorld<MainWorld>("MainWorld");
				m_pressCD = 1.5f;
				break;
			case Level2:
				PlayerPrefs::SetInt("LevelIndex", 2);
				m_menuMusic->StopMusic();
				AbstractGame::Instance()->GetWorldManager()->CreateWorld<MainWorld>("MainWorld");
				m_pressCD = 1.5f;
				break;
			case LevelBackButton:
				m_menuBGSprite->ApplyTexture(m_playSelectedTexture);
				m_pressCD = 1.5f;
				m_Selected = PlayGame;
				m_levelSelect = false;
				break;
			default:
				std::cout << m_Selected << std::endl;
				m_pressCD = 1.5f;

				break;
			}
		}
	}
}

void MenuUI::OnLevelSelect()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) | sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_Selected = Level1;
		m_menuBGSprite->ApplyTexture(m_levelSelected1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) | sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_Selected = Level2;
		m_menuBGSprite->ApplyTexture(m_levelSelected2);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) | sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_Selected = LevelBackButton;
		m_menuBGSprite->ApplyTexture(m_levelSelectedBack);
	}
}
