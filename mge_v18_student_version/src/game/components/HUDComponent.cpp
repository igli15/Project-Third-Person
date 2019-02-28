#include "HUDComponent.h"
#include "mge\components\CanvasComponent.h"
#include "mge\components\UISpriteRenderer.h"
#include "game\HUD.h"
#include <iostream>

HUDComponent::HUDComponent()
{

}


HUDComponent::~HUDComponent()
{

}

void HUDComponent::Start()
{
	m_maxInk = 100;
	SetMaxInk(m_maxInk);
}

void HUDComponent::UpdateInkStatus(float pCurrentInk, int pPlayer)
{
	if (pPlayer == 1)
	{
		m_currentInkPOne = pCurrentInk;
		float spriteScaleP1 = m_currentInkPOne / m_maxInk;
		dynamic_cast<HUD*> (m_gameObject)->playerOneInkSpriteBar->GetSprite()->setScale(1, spriteScaleP1);
		
	}

	else if (pPlayer == 2)
	{
		m_currentInkPTwo = pCurrentInk;
		float spriteScaleP2 = m_currentInkPTwo / m_maxInk;
		dynamic_cast<HUD*> (m_gameObject)->playerTwoInkSpriteBar->GetSprite()->setScale(1, spriteScaleP2);
	}
	else {
		std::cout << "Player with this number doesn't exit " << pPlayer << std::endl;
	}
}

void HUDComponent::UpdateTilesCovered(float percentageOfTilesCovered)
{

}

void HUDComponent::SetMaxInk(float pMaxInk)
{
	m_maxInk = pMaxInk;
	m_currentInkPOne = pMaxInk;
	m_currentInkPTwo = pMaxInk;
}
