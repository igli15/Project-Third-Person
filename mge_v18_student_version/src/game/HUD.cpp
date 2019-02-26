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
	m_playerInk = nullptr;
	playerInkSprite = nullptr;
}

void HUD::Load()
{
	this->AddComponent<CanvasComponent>();
	this->AddComponent<HUDComponent>();
}

void HUD::Awake()
{
}

void HUD::Start()
{
	m_playerInk = AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("playerInk");
	playerInkSprite = AddComponent<UISpriteRenderer>();
	playerInkSprite->ApplyTexture(m_playerInk);

}

void HUD::Update(float pStep)
{

}

void HUD::OnDestroy()
{
}
