#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <map>
#include <string>
#include <GL/glew.h>
#include "SFML/Graphics.hpp"

enum TextureType
{
	DIFFUSE,
	SPECULAR
};

class Texture
{
	public:
		Texture();
		virtual ~Texture();

		GLuint getId();

		TextureType Type();

		void SetType(TextureType type);

		void InnerSetImage(sf::Image* image);

		sf::Image* Image();

	protected:

	    //OpenGL id for texture buffer
		GLuint _id;

		TextureType m_type;

		sf::Image* m_image;

};

#endif // TEXTURE_HPP
