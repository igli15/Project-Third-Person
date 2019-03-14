#pragma once
#include "mge\core\GameObject.hpp"
#include "mge\components\CanvasComponent.h"
#include "mge\components\UISpriteRenderer.h"
#include "mge\components\TextComponent.h"
#include "mge/components/AudioSource.h"
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
	UISpriteRenderer*lavaInkSpriteBar;
	UISpriteRenderer*iceInkSpriteBar;
	UISpriteRenderer* inkUIOverlay;
	UISpriteRenderer* inkUIBackground;
	UISpriteRenderer* percentLavaBar;
	UISpriteRenderer* percentIceBar;
	UISpriteRenderer* inkWarningIce;
	UISpriteRenderer* inkWarningLava;
	UISpriteRenderer* crownLead;

	TextComponent * timerNumber;
	TextComponent * iceRespawnText;
	TextComponent * lavaRespawnText;

	
	sf::Text * timerText;
	sf::Text * lavaRespawnTimer;
	sf::Text * iceRespawnTimer;

	float timeRunningOut = 1.0f;

	float icePercantage = 0;
	float lavaPercatange = 0;

	void ShowInkWarningLava();
	void ShowInkWarningIce();
	void DontShowInkWarningLava();
	void DontShowInkWarningIce();


	static HUDComponent* GetHudComponent();
	void SetRespawnTime(int pPlayer, float pRespawnTime);
	void SetPlayerTilePercentage(int pPlayer, float pPercent);
	AudioSource* m_audioSource;
private:

	sf::Texture * m_inkBarLava;
	sf::Texture * m_inkBarIce;
	sf::Texture * m_inkUIOverlay;
	sf::Texture * m_inkUIBackground;
	sf::Texture * m_percentLavaBarTexture;
	sf::Texture * m_percentIceBarTexture;
	sf::Texture * m_inkWarningIce;
	sf::Texture * m_inkWarningLava;
	sf::Texture* m_blank;
	sf::Texture* m_crownLava;
	sf::Texture* m_crownIce;

	sf::Font * m_timerFont;
	sf::Clock m_gameClock;
	float m_gameLength;
	bool lavaDead = false;
	bool iceDead = false;
	bool leadChanged = false;
	float m_time;
	float m_lavaRespawnTime;
	float m_iceRespawnTime;
	static HUDComponent* m_hudComponent;

	sf::Music* m_backgroundMusic;
	sf::Sound* m_counter;
};

