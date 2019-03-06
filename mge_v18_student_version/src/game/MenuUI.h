#pragma once
#include "mge\core\GameObject.hpp"
#include "mge\components\CanvasComponent.h"
#include "mge\components\UISpriteRenderer.h"
#include "mge\components\TextComponent.h"
#include <SFML/System.hpp>
#include "lua.h"
#include "mge\components\UISpriteRenderer.h"
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
private:
	enum Selected
	{
		PlayGame,
		Controls,
		ExitGame,
		NONE
	};
	Selected m_Selected = NONE;
	bool m_controlsLocked = false;
	UISpriteRenderer* m_menuBGSprite;
	float m_pressCD = 0.0f;
	sf::Texture * m_menuBGTexture;
	sf::Texture * m_playSelectedTexture;
	sf::Texture * m_controlsSelectedTexture;
	sf::Texture * m_exitGameSelectedTexture;
	sf::Texture * m_ControlScreen;
	sf::Texture * m_ControlScreenPressed;

};

