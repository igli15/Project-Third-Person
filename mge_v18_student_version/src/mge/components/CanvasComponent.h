#pragma once
#include<SFML\Graphics.hpp>
#include "mge\core\AbstractGame.hpp"
#include<vector>
#include "mge\core\Component.h"

class UISpriteRenderer;

class CanvasComponent : public Component
{

public:
	CanvasComponent();
	~CanvasComponent();
	void AddSpriteRenderer(UISpriteRenderer* pUISpriteRenderer);
	void DrawAllUISprites();
	void Awake() override;

private:
	std::vector<UISpriteRenderer*> m_uISpriteRenderers;


};