#include "ResolutionUI.h"
#include "mge\core\AbstractGame.hpp"
#include "mge\components\CanvasComponent.h"
#include "mge\core\GameObject.hpp"
#include "mge\components\UISpriteRenderer.h"
#include "mge\core\ResourceManager.h"
#include <SFML\System.hpp>
#include "MainWorld.h"
#include "mge/core/WorldManager.h"
#include "mge/core/PlayerPrefs.h"
#include "game/MenuScene.h"

ResolutionUI::ResolutionUI()
{
}


ResolutionUI::~ResolutionUI()
{

}

void ResolutionUI::Load()
{

	m_blazePrevails = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("blazePrevails");
	m_briskPrevails = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("briskPrevails");
	m_draw = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("draw");

	m_resoLavaBar = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("resoLavaBar");
	m_resoIceBar = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("resoIceBar");
	m_scoreBarBGTexture = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("scoreBarBG");
	m_scoreBarOverlayTexture = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("scoreBarOverlay");

	m_resoNone = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("resoNone");
	m_resoReplay = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("resoReplay");
	m_resoMenu = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("resoMenu");


	//BOTTOM PART
	//BackgroundSprite
	m_botResoBGSprite = AddComponent<UISpriteRenderer>();
	m_botResoBGSprite->ApplyTexture(m_resoNone);

	//add ScoreBar Overlay
	m_scoreBarOverlaySprite = AddComponent<UISpriteRenderer>();
	m_scoreBarOverlaySprite->ApplyTexture(m_scoreBarOverlayTexture);

	//add Right BackgroundImage with Winner
	m_topResoBGSprite = AddComponent<UISpriteRenderer>();
	if (PlayerPrefs::GetFloat("LavaPercentage") > PlayerPrefs::GetFloat("IcePercentage"))
	{
		m_topResoBGSprite->ApplyTexture(m_blazePrevails);
	}
	else if (PlayerPrefs::GetFloat("LavaPercentage") < PlayerPrefs::GetFloat("IcePercentage"))
	{
		m_topResoBGSprite->ApplyTexture(m_briskPrevails);
	}
	else {
		m_topResoBGSprite->ApplyTexture(m_draw);
	}

	//add ScoreBars
	m_blazeScoreBarSprite = AddComponent<UISpriteRenderer>();
	m_blazeScoreBarSprite->ApplyTexture(m_resoLavaBar);
	m_blazeScoreBarSprite->GetSprite()->setOrigin(0, m_blazeScoreBarSprite->GetSprite()->getGlobalBounds().height/2);
	m_blazeScoreBarSprite->GetSprite()->setPosition(451, 660);
	m_blazeScoreBarSprite->GetSprite()->setScale(PlayerPrefs::GetFloat("LavaPercentage"),1);

	m_briskScoreBarSprite = AddComponent<UISpriteRenderer>();
	m_briskScoreBarSprite->ApplyTexture(m_resoIceBar);
	m_briskScoreBarSprite->GetSprite()->setOrigin(m_briskScoreBarSprite->GetSprite()->getGlobalBounds().width, m_briskScoreBarSprite->GetSprite()->getGlobalBounds().height / 2);
	m_briskScoreBarSprite->GetSprite()->setPosition(451 + m_briskScoreBarSprite->GetSprite()->getGlobalBounds().width, 660);
	m_briskScoreBarSprite->GetSprite()->setScale(PlayerPrefs::GetFloat("IcePercentage"), 1);


	//add Background of scores
	m_scoreBarBGSprite = AddComponent<UISpriteRenderer>();
	m_scoreBarBGSprite->ApplyTexture(m_scoreBarBGTexture);
	GameObject::Load();
}

void ResolutionUI::Awake()
{
	m_Selected = NONE;
	GameObject::Awake();
}

void ResolutionUI::Start()
{
	GameObject::Start();
}

void ResolutionUI::Update(float pStep)
{
	GameObject::Update(pStep);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) | sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		std::cout << "Show me replay sprite" << std::endl;
		//show Play again Selected Sprite
		m_Selected = PlayAgain;
		m_botResoBGSprite->ApplyTexture(m_resoReplay);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) | sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		std::cout << "Show me Menu sprite" << std::endl;

		//show Menu selected sprite
		m_Selected = MainMenu;
		m_botResoBGSprite->ApplyTexture(m_resoMenu);

	}

	OnSelected();

}

void ResolutionUI::OnDestroy()
{
	GameObject::OnDestroy();
}

void ResolutionUI::OnSelected()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) | sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		switch (m_Selected)
		{
		case PlayAgain:
			//change later on to playerprefs of selected level (1|2)
			
				AbstractGame::Instance()->GetWorldManager()->CreateWorld<MainWorld>("MainWorld");
			
			break;
		case MainMenu:
			AbstractGame::Instance()->GetWorldManager()->CreateWorld<MenuScene>("MenuScene");
			break;
		default:
			break;
		}
	}
}
