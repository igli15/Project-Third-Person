#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <map>
#include <string>
#include <GL/glew.h>

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

		static Texture* load(const std::string& pTexturePath, TextureType type = TextureType::DIFFUSE);

		GLuint getId();

		TextureType Type();

	protected:
	   

        static Texture* _loadFromFile(const std::string pTexturePath);

	    //OpenGL id for texture buffer
		GLuint _id;

		TextureType m_type;
};

#endif // TEXTURE_HPP
