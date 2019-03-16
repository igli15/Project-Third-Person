#pragma once
#include "mge\core\GameObject.hpp"
#include "mge\components\CanvasComponent.h"
#include "mge\components\UISpriteRenderer.h"
#include "mge\components\TextComponent.h"
#include <SFML/System.hpp>
#include "lua.h"
#include "mge\components\UISpriteRenderer.h"
#include "mge/components/AudioSource.h"
#include <SFML\Audio.hpp>
#include "mge/core/AbstractGame.hpp"
#include "mge/core/ResourceManager.h"
#include "mge/core/GameObject.hpp"

class ResolutionUI : public GameObject
{
public:
	ResolutionUI();
	virtual ~ResolutionUI();
	void Load() override;
	void Awake() override;
	void Start() override;
	void Update(float pStep) override;
	virtual void OnDestroy() override;
	void OnSelected();

private:
	enum Selected
	{
		PlayAgain,
		MainMenu,
		NONE
	};
	Selected m_Selected = NONE;
	UISpriteRenderer* m_topResoBGSprite;
	UISpriteRenderer* m_botResoBGSprite;
	UISpriteRenderer* m_blazeScoreBarSprite;
	UISpriteRenderer* m_briskScoreBarSprite;
	UISpriteRenderer* m_scoreBarBGSprite;
	UISpriteRenderer* m_scoreBarOverlaySprite;

	sf::Texture* m_blazePrevails;
	sf::Texture* m_briskPrevails;
	sf::Texture* m_draw;
	sf::Texture* m_resoNone;
	sf::Texture* m_resoReplay;
	sf::Texture* m_resoMenu;
	sf::Texture* m_resoLavaBar;
	sf::Texture* m_resoIceBar;
	sf::Texture* m_scoreBarBGTexture;
	sf::Texture* m_scoreBarOverlayTexture;

	float m_selectCD;
	TextComponent* m_leftNumbers;
	TextComponent* m_rightNumbers;

	sf::Text * m_leftNumberText;
	sf::Text * m_rightNumberText;
	sf::Font * m_timerFont;
	
	AudioSource* m_audioSource;
	sf::Music * m_initMusic;
};

