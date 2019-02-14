#pragma once
#include <SFML\Graphics.hpp>
#include "mge\core\AbstractGame.hpp"
#include "mge\core\Component.h"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"

class CanvasComponent;

class UISpriteRenderer : public Component
{
public:
	UISpriteRenderer();
	virtual ~UISpriteRenderer();
	void DrawSprite();
	void InitRenderingQuad();
	void Awake() override;
private:

	Texture* m_texture = nullptr;

	static ShaderProgram* m_shaderProgram;
	static void InitShaderProgram();
	GLuint m_quadVAO;
};

