#pragma once
#include "mge\core\Component.h"
#include "mge\components\CanvasComponent.h"
#include "mge\components\UISpriteRenderer.h"
#include "game\HUD.h"

class HUDComponent : public Component
{
public:
	HUDComponent();
	virtual ~HUDComponent();
	void UpdateInkStatus(float currentInk, float maxInk);
	void UpdateTilesCovered(float percentageOfTilesCovered);
private:
	sf::Texture m_playerInk;
};

