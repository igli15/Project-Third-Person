#pragma once

#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/lua/LuaProgram.h"

class ResourceManager
{

private:
	std::map<std::string, Texture*> m_textureMap;
	std::map<std::string, Mesh*> m_meshMap;
	std::map<std::string, AbstractMaterial*> m_materialMap;
	LuaProgram* m_luaProgram;
	
public:
	ResourceManager();
	virtual ~ResourceManager();

	Texture* LoadTexture(const std::string &path, const std::string &tag,TextureType textureType);
	Mesh* LoadMesh(const std::string &path, const std::string &tag);

	
	Texture* GetTexture(const std::string &tag);
	Mesh* GetMesh(const std::string &tag);
	

	AbstractMaterial* RegisterMaterial(AbstractMaterial* mat, const std::string &tag);
	AbstractMaterial* GetMaterial(const std::string &tag);

	void LoadResourcesFromLua();
	void LuaLoadMeshes();
};

