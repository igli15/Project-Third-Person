#pragma once

#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"


class ResourceManager
{

private:
	std::map<std::string, Texture*> m_textureMap;
	std::map<std::string, Mesh*> m_meshMap;

public:
	ResourceManager();
	virtual ~ResourceManager();

	Texture* LoadTexture(const std::string &path, const std::string &tag,TextureType textureType);
	Mesh* LoadMesh(const std::string &path, const std::string &tag);

	
	Texture* GetTexture(const std::string &tag);
	Mesh* GetMesh(const std::string &tag);
};

