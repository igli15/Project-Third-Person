#include "HUD.h"
#include "mge\components\CanvasComponent.h"
#include "mge\core\GameObject.hpp"
#include "game\components\HUDComponent.h"
#include "mge\components\UISpriteRenderer.h"
#include "mge\core\ResourceManager.h"

HUD::HUD()
{

}


HUD::~HUD()
{
	
}

void HUD::Load()
{
	GameObject::Load();
	this->AddComponent<HUDComponent>();

	//Get SFML Textures
	m_playerOneInkText = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("playerOneInkText");
	m_playerTwoInkText = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("playerTwoInkText");
	m_inkBarPlayerOne = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("inkPlayerOne");
	m_inkBarPlayerTwo = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("inkPlayerTwo");
	m_inkBarOutlines = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("inkBarOutlines");
	
	//Create Sprite and assign Texture to Sprite
	playerOneInkSpriteText = AddComponent<UISpriteRenderer>();
	playerOneInkSpriteText->ApplyTexture(m_playerOneInkText);
	playerOneInkSpriteText->GetSprite()->setPosition(10, 10);

	playerTwoInkSpriteText = AddComponent<UISpriteRenderer>();
	playerTwoInkSpriteText->ApplyTexture(m_playerTwoInkText);
	playerTwoInkSpriteText->GetSprite()->setPosition(GetMirroredPostionX(10.0f, playerTwoInkSpriteText), 10);


	glm::vec2 playerBarPosition = glm::vec2(playerOneInkSpriteText->GetSprite()->getGlobalBounds().width + 20, 10);

	playerOneInkSpriteBar = AddComponent<UISpriteRenderer>();
	playerOneInkSpriteBar->ApplyTexture(m_inkBarPlayerOne);
	playerOneInkSpriteBar->GetSprite()->setPosition(playerBarPosition.x, playerBarPosition.y);

	playerTwoInkSpriteBar = AddComponent<UISpriteRenderer>();
	playerTwoInkSpriteBar->ApplyTexture(m_inkBarPlayerTwo);
	playerTwoInkSpriteBar->GetSprite()->setPosition(GetMirroredPostionX(playerBarPosition.x, playerTwoInkSpriteBar) + playerTwoInkSpriteBar->GetSprite()->getGlobalBounds().width, playerBarPosition.y);
	playerTwoInkSpriteBar->GetSprite()->setOrigin(playerTwoInkSpriteBar->GetSprite()->getGlobalBounds().width, 0);

	inkBarOutlinesPlayerOne = AddComponent<UISpriteRenderer>();
	inkBarOutlinesPlayerOne->ApplyTexture(m_inkBarOutlines);
	inkBarOutlinesPlayerOne->GetSprite()->setPosition(playerBarPosition.x - 0.9f, playerBarPosition.y-1.1f);

	inkBarOutlinesPlayerTwo = AddComponent<UISpriteRenderer>();
	inkBarOutlinesPlayerTwo->ApplyTexture(m_inkBarOutlines);
	inkBarOutlinesPlayerTwo->GetSprite()->setPosition(GetMirroredPostionX(playerBarPosition.x+0.9f, playerTwoInkSpriteBar), playerBarPosition.y- 1.1f);
}

void HUD::Awake()
{
	GameObject::Awake();
}

void HUD::Start()
{
	GameObject::Start();

	
}

void HUD::Update(float pStep)
{
	GameObject::Update(pStep);
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
