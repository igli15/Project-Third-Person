#pragma once
#include<SFML\Graphics.hpp>
#include "mge\core\AbstractGame.hpp"
#include<vector>
#include "mge\core\Component.h"
#include "glm.hpp"
#include "GL/glew.h"
#include <algorithm>

class UISpriteRenderer;
class TextComponent;

class CanvasComponent : public Component
{

public:
	CanvasComponent();
	~CanvasComponent();
	void AddSpriteRenderer(UISpriteRenderer* pUISpriteRenderer);
	void AddTextComponent(TextComponent* textComponent);
	
	void RemoveSpriteRenderer(UISpriteRenderer* pUISpriteRenderer);
	void RemoveTextComponent(TextComponent* textComponent);
	void DrawAllUISprites(sf::RenderWindow* window);
	void DrawAllTexts(sf::RenderWindow* window);
	void Awake() override;

private:
	std::vector<UISpriteRenderer*> m_uISpriteRenderers;
	std::vector<TextComponent*> m_textComponents;
	
	float m_canvasWidth = 800;
	float m_canvasHeight = 600;

	//just for init is set to identity matrix
	glm::mat4 m_projectionMat;

};