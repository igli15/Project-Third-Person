#pragma once
#include "mge\core\GameObject.hpp"
#include "mge\components\CanvasComponent.h"
#include "mge\components\UISpriteRenderer.h"
#include "lua.h"
//include uispriterenderer

class HUDComponent;

class HUD : public GameObject
{
public:
	HUD();
	virtual ~HUD();
	void Load() override;
	void Awake() override;
	void Start() override;
	void Update(float pStep) override;
	virtual void OnDestroy() override;
	float GetMirroredPostionX(float xPosition, UISpriteRenderer* sprite);
	//Sprites
	UISpriteRenderer* playerOneInkSpriteText;
	UISpriteRenderer*playerTwoInkSpriteText;
	UISpriteRenderer*playerOneInkSpriteBar;
	UISpriteRenderer*playerTwoInkSpriteBar;
	UISpriteRenderer* inkBarOutlinesPlayerOne;
	UISpriteRenderer* inkBarOutlinesPlayerTwo;

	static HUDComponent* GetHudComponent();
private:
	sf::Texture * m_playerOneInkText;
	sf::Texture * m_playerTwoInkText;
	sf::Texture * m_inkBarPlayerOne;
	sf::Texture * m_inkBarPlayerTwo;
	sf::Texture * m_inkBarOutlines;

	static HUDComponent* m_hudComponent;
};

