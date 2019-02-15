#pragma once
#include<SFML\Graphics.hpp>
#include "mge\core\AbstractGame.hpp"
#include<vector>
#include "mge\core\Component.h"
#include "glm.hpp"
#include "GL/glew.h"

class UISpriteRenderer;

class CanvasComponent : public Component
{

public:
	CanvasComponent();
	~CanvasComponent();
	void AddSpriteRenderer(UISpriteRenderer* pUISpriteRenderer);
	void DrawAllUISprites(sf::RenderWindow* window);
	void Awake() override;

private:
	std::vector<UISpriteRenderer*> m_uISpriteRenderers;
	
	float m_canvasWidth = 800;
	float m_canvasHeight = 600;

	//just for init is set to identity matrix
	glm::mat4 m_projectionMat;

};