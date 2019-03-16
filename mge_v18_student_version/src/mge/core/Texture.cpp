#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include "mge/core/Texture.hpp"

Texture::Texture(): _id() {
    glGenTextures (1, &_id);
}

Texture::~Texture()
{
	glDeleteTextures(1, &_id);
	m_image = nullptr;
	delete m_image;
}

GLuint Texture::getId() {
	return _id;
}

TextureType Texture::Type()
{
	return m_type;
}

void Texture::SetType(TextureType type)
{
	m_type = type;
}

void Texture::InnerSetImage(sf::Image * image)
{
	m_image = image;
}

sf::Image * Texture::Image()
{
	return m_image;
}











