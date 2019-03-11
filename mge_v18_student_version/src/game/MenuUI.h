#pragma once
#include "mge\core\GameObject.hpp"
#include "mge\components\CanvasComponent.h"
#include "mge\components\UISpriteRenderer.h"
#include "mge\components\TextComponent.h"
#include <SFML/System.hpp>
#include "lua.h"
#include "mge\components\UISpriteRenderer.h"
#include "mge\components\AudioSource.h"
class MenuUI : public GameObject
{
public:
	MenuUI();
	virtual ~MenuUI();
	void Load() override;
	void Awake() override;
	void Start() override;
	void Update(float pStep) override;
	virtual void OnDestroy() override;
	void OnHoldControls();
	void OnLevelSelect();
private:
	enum Selected
	{
		PlayGame,
		Controls,
		ExitGame,
		NONE,
		Level1,
		Level2,
		LevelBackButton
	};
	Selected m_Selected = NONE;
	UISpriteRenderer* m_menuBGSprite;
	bool m_controlsLocked = false;
	bool m_levelSelect = false;
	bool m_hasChanged = false;
	float m_pressCD = 0.0f;
	sf::Texture * m_menuBGTexture;
	sf::Texture * m_playSelectedTexture;
	sf::Texture * m_controlsSelectedTexture;
	sf::Texture * m_exitGameSelectedTexture;
	sf::Texture * m_ControlScreen;
	sf::Texture * m_ControlScreenPressed;

	sf::Texture* m_levelSelectedNone;
	sf::Texture* m_levelSelected1;
	sf::Texture* m_levelSelected2;
	sf::Texture* m_levelSelectedBack;

	sf::Music* m_menuMusicSF;
	AudioSource* m_menuMusic;

	AudioSource* m_selectingButton;

	AudioSource* m_pressingButton;


};

