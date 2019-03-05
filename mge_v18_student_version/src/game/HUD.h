#pragma once
#include "mge\core\GameObject.hpp"
#include "mge\components\CanvasComponent.h"
#include "mge\components\UISpriteRenderer.h"
#include "mge\components\TextComponent.h"
#include <SFML/System.hpp>
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
	UISpriteRenderer* inkUIOverlay;
	UISpriteRenderer* inkUIBackground;
	TextComponent * leftNumbers;
	TextComponent * colon;
	TextComponent * rightNumbers;

	sf::Text * leftNumberText;
	sf::Text * rightNumberText;
	sf::Text * colonText;


	float icePercantage = 0;
	float lavaPercatange = 0;

	static HUDComponent* GetHudComponent();
private:
	sf::Texture * m_playerOneInkText;
	sf::Texture * m_playerTwoInkText;
	sf::Texture * m_inkBarPlayerOne;
	sf::Texture * m_inkBarPlayerTwo;
	sf::Texture * m_inkUIOverlay;
	sf::Texture * m_inkUIBackground;
	sf::Font * m_timerFont;
	sf::Clock m_gameClock;
	int m_gameLength;
	std::string m_time;

	static HUDComponent* m_hudComponent;

};

