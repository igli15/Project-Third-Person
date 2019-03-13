#include "HUD.h"
#include "mge\components\CanvasComponent.h"
#include "mge\core\GameObject.hpp"
#include "game\components\HUDComponent.h"
#include "mge\components\UISpriteRenderer.h"
#include "mge\core\ResourceManager.h"
#include "mge\components\TextComponent.h"
#include <SFML\System.hpp>
#include "MainWorld.h"
#include"components\GridComponent.h"
#include "mge\core\PlayerPrefs.h"
#include "mge\core\WorldManager.h"
#include "game\ResolutionScreen.h"

HUDComponent* HUD::m_hudComponent;

HUD::HUD()
{

}


HUD::~HUD()
{

}

void HUD::Load()
{
	GameObject::Load();
	m_hudComponent = this->AddComponent<HUDComponent>();

	//Get SFML Textures
	m_inkBarLava = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("lavaFillBar");
	m_inkBarIce = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("iceFillBar");
	m_inkUIOverlay = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("inkUIOverlay");
	m_inkUIBackground = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("inkUIBackground");
	m_percentLavaBarTexture = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("percentageLavaBar");
	m_percentIceBarTexture = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("percentageIceBar");
	m_timerFont = AbstractGame::Instance()->GetResourceManager()->GetSFMLFont("theBoldFont");


	////Create Sprite and assign Texture to Sprite

	timerNumber = AddComponent<TextComponent>();
	timerText = timerNumber->CreateText(m_timerFont);
	timerText->setFillColor(sf::Color(224,201,166));
	timerText->setCharacterSize(36);
	timerText->setString("");
	timerText->setPosition(930, 985);


	lavaRespawnText = AddComponent<TextComponent>();
	lavaRespawnTimer = lavaRespawnText->CreateText(m_timerFont);
	lavaRespawnTimer->setFillColor(sf::Color(133, 83, 35));
	lavaRespawnTimer->setCharacterSize(36);
	lavaRespawnTimer->setString("");
	lavaRespawnTimer->setPosition(817, 1025);

	iceRespawnText = AddComponent<TextComponent>();
	iceRespawnTimer = iceRespawnText->CreateText(m_timerFont);
	iceRespawnTimer->setFillColor(sf::Color(133, 83, 35));
	iceRespawnTimer->setCharacterSize(36);
	iceRespawnTimer->setString("");
	iceRespawnTimer->setPosition(1075, 1023);

	inkUIOverlay = AddComponent<UISpriteRenderer>();
	inkUIOverlay->ApplyTexture(m_inkUIOverlay);
	inkUIOverlay->GetSprite()->setPosition(0,0);
	glm::vec2 playerBarPosition = glm::vec2(97, 100);

	lavaInkSpriteBar = AddComponent<UISpriteRenderer>();
	lavaInkSpriteBar->ApplyTexture(m_inkBarLava);
	lavaInkSpriteBar->GetSprite()->setPosition(playerBarPosition.x, playerBarPosition.y);
	lavaInkSpriteBar->GetSprite()->setOrigin(0, lavaInkSpriteBar->GetSprite()->getGlobalBounds().height);

	iceInkSpriteBar = AddComponent<UISpriteRenderer>();
	iceInkSpriteBar->ApplyTexture(m_inkBarIce);
	iceInkSpriteBar->GetSprite()->setPosition(GetMirroredPostionX(playerBarPosition.x, iceInkSpriteBar)-5, playerBarPosition.y);
	iceInkSpriteBar->GetSprite()->setOrigin(0, iceInkSpriteBar->GetSprite()->getGlobalBounds().height);

	inkUIBackground = AddComponent<UISpriteRenderer>();
	inkUIBackground->ApplyTexture(m_inkUIBackground);
	inkUIBackground->GetSprite()->setPosition(0, 0);

	percentLavaBar = AddComponent<UISpriteRenderer>();
	percentLavaBar->ApplyTexture(m_percentLavaBarTexture);
	percentLavaBar->GetSprite()->setPosition(960- percentLavaBar->GetSprite()->getGlobalBounds().width/2, 965);
	percentLavaBar->GetSprite()->setScale(0.5f, 1);

	percentIceBar = AddComponent<UISpriteRenderer>();
	percentIceBar->ApplyTexture(m_percentIceBarTexture);
	percentIceBar->GetSprite()->setPosition(1034, 965);
	percentIceBar->GetSprite()->setOrigin(percentIceBar->GetSprite()->getGlobalBounds().width, 0);
	percentIceBar->GetSprite()->setScale(0.5f, 1);

	//--------------------------------MUSIC
	m_backgroundMusic = AbstractGame::Instance()->GetResourceManager()->GetMusic("levelMusic");
	m_audioSource = AddComponent<AudioSource>();
	m_audioSource->SetMusic(m_backgroundMusic);

}

void HUD::Awake()
{
	GameObject::Awake();
}

void HUD::Start()
{
	GameObject::Start();
	m_gameLength = 30;
	m_gameClock.restart();
	SetRespawnTime(1, 22);
	SetRespawnTime(2, 22);
	m_audioSource->SetVolume(90);
	m_audioSource->PlayMusic();
}

void HUD::Update(float pStep)
{
	GameObject::Update(pStep);
	float cD = m_gameClock.restart().asSeconds();
	m_gameLength = m_gameLength - cD;
	sf::FloatRect textRect = timerText->getLocalBounds();
	timerText->setOrigin(textRect.width / 2, textRect.height / 2);
	timerText->setString("" + std::to_string((int) m_gameLength));
	timerText->setPosition(956, 999);

	if (m_gameLength <= 0)
	{
		PlayerPrefs::SetFloat("IcePercentage", dynamic_cast<MainWorld*>(GetWorld())->GetGrid()->GetTilePercantage(TileType::ICE)/100);
		PlayerPrefs::SetFloat("LavaPercentage", dynamic_cast<MainWorld*>(GetWorld())->GetGrid()->GetTilePercantage(TileType::LAVA)/100);
		m_audioSource->StopMusic();

		AbstractGame::Instance()->GetWorldManager()->CreateWorld<ResolutionScreen>("ResolutionScreen");
		//covered tile function

		//end game (call reso Screen)
	}
	if(lavaDead)
	{ 
		m_lavaRespawnTime = m_lavaRespawnTime - cD;
		sf::FloatRect textRectLava = lavaRespawnTimer->getLocalBounds();
		lavaRespawnTimer->setOrigin(textRectLava.width / 2, textRectLava.height / 2);
		lavaRespawnTimer->setString("" + std::to_string((int)m_lavaRespawnTime));
		lavaRespawnTimer->setPosition(826, 1035);
		if (m_lavaRespawnTime <= 0)
		{
			m_audioSource->PlayOneShotSound("playerRespawnSound");
			lavaRespawnTimer->setString("");
			lavaDead = false;
		}
	}
	if (iceDead)
	{
		m_iceRespawnTime = m_iceRespawnTime - cD;
		sf::FloatRect textRectIce = iceRespawnTimer->getLocalBounds();
		iceRespawnTimer->setOrigin(textRectIce.width / 2, textRectIce.height / 2);
		iceRespawnTimer->setString("" + std::to_string((int)m_iceRespawnTime));
		iceRespawnTimer->setPosition(1085, 1035);
		if (m_iceRespawnTime <= 0)
		{
			m_audioSource->PlayOneShotSound("playerRespawnSound");
			iceRespawnTimer->setString("");
			iceDead = false;
		}
	}
	

}

void HUD::OnDestroy()
{
}

float HUD::GetMirroredPostionX(float xPosition, UISpriteRenderer* sprite)
{
	float spriteWidth = sprite->GetSprite()->getGlobalBounds().width;
	float desiredSpritePositionX = (1920.0f - xPosition - spriteWidth);
	return desiredSpritePositionX;
}

HUDComponent * HUD::GetHudComponent()
{
	return m_hudComponent;
}

void HUD::SetRespawnTime(int pPlayer, float pRespawnTime)
{
	if (pPlayer == 1)
	{
		m_audioSource->PlayOneShotSound("iceDeath");
		m_lavaRespawnTime = pRespawnTime + 1.9f;
		lavaRespawnTimer->setString("" + std::to_string((int)pRespawnTime));
		lavaDead = true;
	}
	if (pPlayer == 2)
	{
		m_audioSource->PlayOneShotSound("lavaDeath");
		m_iceRespawnTime = pRespawnTime + 1.9f;
		iceRespawnTimer->setString("" + std::to_string((int)pRespawnTime));
		iceDead = true;
	}
}

void HUD::SetPlayerTilePercentage(int pPlayer, float pPercent)
{
	if (pPlayer == 1)
	{
		percentLavaBar->GetSprite()->setScale(pPercent/100.0f, 1);
		percentIceBar->GetSprite()->setScale(1-(pPercent / 100.0f), 1);
		m_audioSource->PlayOneShotSound("lavaAttack");
		
	}

	if (pPlayer == 2)
	{
		percentIceBar->GetSprite()->setScale(pPercent / 100.0f, 1);
		percentLavaBar->GetSprite()->setScale(1 - (pPercent / 100.0f), 1);
		m_audioSource->PlayOneShotSound("iceAttack");
	}
}



