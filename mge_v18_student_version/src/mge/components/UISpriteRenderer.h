#pragma once
#include <SFML\Graphics.hpp>
#include "mge\core\AbstractGame.hpp"
#include "mge\core\Component.h"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "glm.hpp"

class CanvasComponent;

class UISpriteRenderer : public Component
{
public:
	UISpriteRenderer();
	virtual ~UISpriteRenderer();
	void DrawSprite(glm::mat4 projection);
	void InitRenderingQuad();
	void Awake() override;
	void SetTexture(Texture* tex);
	void SetTintColor(glm::vec3 tint);

private:

	Texture* m_texture = nullptr;
	glm::vec3 m_tintColor = glm::vec3(1, 1, 1);
	static ShaderProgram* m_shaderProgram;
	static void InitShaderProgram();
	GLuint m_quadVAO;
};

