#include "HUDComponent.h"
#include "mge\components\CanvasComponent.h"
#include "mge\components\UISpriteRenderer.h"
#include "game\HUD.h"
#include <iostream>
#include "mge\components\AudioSource.h"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/GameObject.hpp"

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
	
	hud = dynamic_cast<HUD*> (m_gameObject);
}

void HUDComponent::UpdateInkStatus(float pCurrentInk, int pPlayer)
{
	if (pPlayer == 1)
	{
		
		m_currentInkPOne = pCurrentInk;
		float spriteScaleP1 = m_currentInkPOne / m_maxInk;
		hud->lavaInkSpriteBar->GetSprite()->setScale(spriteScaleP1, 1);
		if (spriteScaleP1 < 0.3f)
		{
			hud->ShowInkWarningLava();
		} else { hud->DontShowInkWarningLava(); }
	}

	else if (pPlayer == 2)
	{
		m_currentInkPTwo = pCurrentInk;
		float spriteScaleP2 = m_currentInkPTwo / m_maxInk;
		hud->iceInkSpriteBar->GetSprite()->setScale(spriteScaleP2, 1);
		if (spriteScaleP2 < 0.3f)
		{
			hud->ShowInkWarningIce();
		}
		else { hud->DontShowInkWarningIce(); }
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
