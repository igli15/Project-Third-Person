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
	//m_playerOneInkText = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("playerOneInkText");
	//m_playerTwoInkText = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("playerTwoInkText");
	m_inkBarPlayerOne = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("inkPlayerOne");
	m_inkBarPlayerTwo = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("inkPlayerTwo");
	m_inkUIOverlay = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("inkUIOverlay");
	m_inkUIBackground = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("inkUIBackground");
	m_timerFont = AbstractGame::Instance()->GetResourceManager()->GetSFMLFont("theBoldFont");

	////Create Sprite and assign Texture to Sprite
	//playerOneInkSpriteText = AddComponent<UISpriteRenderer>();
	//playerOneInkSpriteText->ApplyTexture(m_playerOneInkText);
	//playerOneInkSpriteText->GetSprite()->setPosition(10, 10);

	//playerTwoInkSpriteText = AddComponent<UISpriteRenderer>();
	//playerTwoInkSpriteText->ApplyTexture(m_playerTwoInkText);
	//playerTwoInkSpriteText->GetSprite()->setPosition(GetMirroredPostionX(10.0f, playerTwoInkSpriteText), 10);

	leftNumbers = AddComponent<TextComponent>();
	leftNumberText = leftNumbers->CreateText(m_timerFont);
	leftNumberText->setFont(*m_timerFont);
	leftNumberText->setCharacterSize(62);
	leftNumberText->setString("");
	leftNumberText->setOrigin(leftNumberText->getGlobalBounds().width / 2, 0);
	leftNumberText->setPosition(930, 500);
	

	inkUIOverlay = AddComponent<UISpriteRenderer>();
	inkUIOverlay->ApplyTexture(m_inkUIOverlay);
	inkUIOverlay->GetSprite()->setPosition(0,0);
	glm::vec2 playerBarPosition = glm::vec2(30, 425);

	playerOneInkSpriteBar = AddComponent<UISpriteRenderer>();
	playerOneInkSpriteBar->ApplyTexture(m_inkBarPlayerOne);
	playerOneInkSpriteBar->GetSprite()->setPosition(playerBarPosition.x, playerBarPosition.y);
	playerOneInkSpriteBar->GetSprite()->setOrigin(0, playerOneInkSpriteBar->GetSprite()->getGlobalBounds().height);

	playerTwoInkSpriteBar = AddComponent<UISpriteRenderer>();
	playerTwoInkSpriteBar->ApplyTexture(m_inkBarPlayerTwo);
	playerTwoInkSpriteBar->GetSprite()->setPosition(GetMirroredPostionX(playerBarPosition.x, playerTwoInkSpriteBar), playerBarPosition.y);
	playerTwoInkSpriteBar->GetSprite()->setOrigin(0, playerTwoInkSpriteBar->GetSprite()->getGlobalBounds().height);

	inkUIBackground = AddComponent<UISpriteRenderer>();
	inkUIBackground->ApplyTexture(m_inkUIBackground);
	inkUIBackground->GetSprite()->setPosition(0, 0);

}

void HUD::Awake()
{
	GameObject::Awake();
}

void HUD::Start()
{
	GameObject::Start();
	m_gameLength = 60;
	m_gameClock.restart();

}

void HUD::Update(float pStep)
{
	GameObject::Update(pStep);
	m_time = std::to_string( (int)(m_gameLength- m_gameClock.getElapsedTime().asSeconds()));
	leftNumberText->setString("" + m_time);

	if (m_gameLength - m_gameClock.getElapsedTime().asSeconds()<=0)
	{
		//covered tile function
		//std::cout << "ICE: " << dynamic_cast<MainWorld*>(GetWorld())->GetGrid()->GetTileCount(TileType::ICE) << std::endl;
		//std::cout << "Lava: " << dynamic_cast<MainWorld*>(GetWorld())->GetGrid()->GetTileCount(TileType::LAVA) << std::endl;

		//end game (call reso Screen)
		
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
