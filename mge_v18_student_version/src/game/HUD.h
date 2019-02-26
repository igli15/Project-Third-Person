#pragma once
#include "mge\core\GameObject.hpp"
#include "mge\components\CanvasComponent.h"
#include "game\components\HUDComponent.h"
#include "mge\components\UISpriteRenderer.h"
#include "lua.h"
//include uispriterenderer


class HUD : public GameObject
{
public:
	HUD();
	virtual ~HUD();
	virtual void Load() override;
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update(float pStep) override;
	virtual void OnDestroy() override;
	UISpriteRenderer* playerInkSprite;

private:
	sf::Texture * m_playerInk;
	sf::Text * m_playerOneInk;
	sf::Text * m_playerTwoInk;
};

