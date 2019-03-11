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
	// = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("scoreBarOverlay");

	m_resoNone = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("resoNone");
	m_resoReplay = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("resoReplay");
	m_resoMenu = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("resoMenu");

	m_timerFont = AbstractGame::Instance()->GetResourceManager()->GetSFMLFont("theBoldFont");
	m_leftNumbers = AddComponent<TextComponent>();
	m_leftNumberText = m_leftNumbers->CreateText(m_timerFont);
	m_leftNumberText->setFillColor(sf::Color(224, 201, 166));
	m_rightNumbers = AddComponent<TextComponent>();
	m_rightNumberText = m_rightNumbers->CreateText(m_timerFont);
	m_rightNumberText->setFillColor(sf::Color(224, 201, 166));
	//BOTTOM PART
	//BackgroundSprite
	m_botResoBGSprite = AddComponent<UISpriteRenderer>();
	m_botResoBGSprite->ApplyTexture(m_resoNone);

	//add ScoreBar Overlay

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

	m_leftNumberText->setFont(*m_timerFont);
	m_leftNumberText->setCharacterSize(36);
	std::string lavaPercentage = std::to_string((int)(PlayerPrefs::GetFloat("LavaPercentage")*100));
	m_leftNumberText->setString("" + lavaPercentage +  "%");

	sf::FloatRect textRectLava = m_leftNumberText->getLocalBounds();
	m_leftNumberText->setOrigin(textRectLava.width / 2,0);

	m_leftNumberText->setPosition(
		462,
		m_blazeScoreBarSprite->GetSprite()->getPosition().y -25
	);

	m_blazeScoreBarSprite->GetSprite()->setScale(PlayerPrefs::GetFloat("LavaPercentage"),1);

	m_briskScoreBarSprite = AddComponent<UISpriteRenderer>();
	m_briskScoreBarSprite->ApplyTexture(m_resoIceBar);
	m_briskScoreBarSprite->GetSprite()->setOrigin(m_briskScoreBarSprite->GetSprite()->getGlobalBounds().width, m_briskScoreBarSprite->GetSprite()->getGlobalBounds().height / 2);
	m_briskScoreBarSprite->GetSprite()->setPosition(451 + m_briskScoreBarSprite->GetSprite()->getGlobalBounds().width, 660);
	
	m_rightNumberText->setFont(*m_timerFont);
	m_rightNumberText->setCharacterSize(36);
	std::string icePercent = std::to_string((int)(PlayerPrefs::GetFloat("IcePercentage") * 100));
	m_rightNumberText->setString("" + icePercent + "%");
	
	sf::FloatRect textRectIce = m_rightNumberText->getLocalBounds();
	m_rightNumberText->setOrigin(textRectIce.width / 2, 0);

	m_rightNumberText->setPosition(1455,m_blazeScoreBarSprite->GetSprite()->getPosition().y - 25);

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
	m_selectCD = 2.0f;
}

void ResolutionUI::Update(float pStep)
{
	GameObject::Update(pStep);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) | sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		/*std::cout << "Show me replay sprite" << std::endl;*/
		//show Play again Selected Sprite
		m_Selected = PlayAgain;
		m_botResoBGSprite->ApplyTexture(m_resoReplay);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) | sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//std::cout << "Show me Menu sprite" << std::endl;

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
	m_selectCD -= 0.03f;
	if (m_selectCD <= 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) | sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		{
			switch (m_Selected)
			{
			case PlayAgain:
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
}
