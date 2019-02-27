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
	void Start()override;
	void UpdateInkStatus(float pCurrentInk, int pPlayer);
	void UpdateTilesCovered(float percentageOfTilesCovered);
	void SetMaxInk(float pMaxInk);

private:
	float m_currentInkPOne;
	float m_currentInkPTwo;
	float m_maxInk;
	float m_tileCoverPercentage;
};

