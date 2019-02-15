#pragma once

#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/lua/LuaProgram.h"
#include "mge/components/AudioSource.h"

class ResourceManager
{

private:
	std::map<std::string, Texture*> m_textureMap;
	std::map<std::string, sf::Texture*> m_sfmlTextures;
	std::map<std::string, Mesh*> m_meshMap;
	std::map<std::string, AbstractMaterial*> m_materialMap;
	std::map<std::string, sf::Music*> m_musicMap;
	std::map<std::string, sf::Sound*> m_soundMap;
	std::vector<sf::SoundBuffer*> m_soundBuffers;  //All sounds need a buffer this keeps track of them so they are cleared
	LuaProgram* m_luaProgram;
	
public:
	ResourceManager();
	virtual ~ResourceManager();

	Texture* LoadTexture(const std::string &path, const std::string &tag,TextureType textureType);
	Mesh* LoadMesh(const std::string &path, const std::string &tag);

	
	Texture* GetTexture(const std::string &tag);
	Mesh* GetMesh(const std::string &tag);

	sf::Texture* LoadSFMLTexture(const std::string &path, const std::string &tag);
	sf::Texture* GetSFMLTexture(const std::string &tag);
	
	AbstractMaterial* RegisterMaterial(AbstractMaterial* mat, const std::string &tag);
	AbstractMaterial* GetMaterial(const std::string &tag);

	sf::Music* LoadMusic(const std::string &path, const std::string &tag);
	sf::Music* GetMusic(const std::string &tag);

	sf::Sound* LoadSound(const std::string &path, const std::string &tag);
	sf::Sound* GetSound(const std::string &tag);


	void LoadResourcesFromLua();
	void LuaLoadMeshes();
	void LuaLoadDiffuseTextures();
	void LuaLoadSpecularTexutres();
	void LuaLoadEmissionTextures();
	void LuaLoadSFMLTextures();
	void LuaLoadSounds();
	void LuaLoadMusics();
};

