#pragma once
#include <SFML\Graphics.hpp>
#include "mge\core\AbstractGame.hpp"
#include "mge\core\Component.h"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "glm.hpp"
#include "GL/glew.h"

class CanvasComponent;

class UISpriteRenderer : public Component
{
public:
	UISpriteRenderer();
	virtual ~UISpriteRenderer();
	void DrawSprite(sf::RenderWindow* window);
	void InitRenderingQuad();
	void Awake() override;
	void SetTintColor(glm::vec3 tint);

	sf::Sprite* ApplyTexture(sf::Texture* texture);

private:

	//Texture* m_texture = nullptr;

	sf::Sprite* m_sprite = nullptr;
	sf::Texture* m_texture = nullptr;

	glm::vec3 m_tintColor = glm::vec3(1, 1, 1);
	static ShaderProgram* m_shaderProgram;
	static void InitShaderProgram();
	GLuint m_quadVAO;
};

