#include "ResourceManager.h"
#include "SFML/Graphics.hpp"
#include "mge/config.hpp"
#include <iostream>
#include <map>
#include <string>
#include <fstream>

ResourceManager::ResourceManager()
{
	m_luaProgram = new LuaProgram("../src/game/Resources.Lua");
	m_luaProgram->CallCurrentProgram();

	LoadTexture(config::MGE_TEXTURE_PATH + "whiteTex.png", "whiteTex",TextureType::RGBAREPLACEMENT);
	LoadTexture(config::MGE_TEXTURE_PATH + "blackTex.png", "blackTex", TextureType::RGBAREPLACEMENT);
	LoadTexture(config::MGE_TEXTURE_PATH + "defaultNormal.png", "flatNormalTex", TextureType::RGBAREPLACEMENT);
}


ResourceManager::~ResourceManager()
{
}


Texture * ResourceManager::LoadTexture(const std::string & path, const std::string & tag, TextureType textureType)
{

	if (m_textureMap.find(tag) != m_textureMap.end())
	{
		std::cout << "A texture with that tag is already created" << std::endl;
		throw;
	}

	// load from file and store in cache
	sf::Image* image = new sf::Image;
	if (image->loadFromFile(path)) {
		//normal image 0,0 is top left, but opengl considers 0,0 to be bottom left, so we flip the image internally
		image->flipVertically();
		//create a wrapper for the id (texture is nothing more than that) and
		//load corresponding data into opengl using this id
		Texture * texture = new Texture();
		texture->SetType(textureType);
		glBindTexture(GL_TEXTURE_2D, texture->getId());

		//If we want specular / normals maps we still have to use rgba instead of SRGB

		if (textureType == TextureType::SPECULAR  || textureType == TextureType::NORMAL || textureType == TextureType::RGBAREPLACEMENT)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getSize().x, image->getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixelsPtr());
		}
		else if (textureType == TextureType::DIFFUSE || TextureType::SRGBREPLACEMENT|| textureType == TextureType::EMISSION)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, image->getSize().x, image->getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixelsPtr());
		}

		//wrap the default tex
		if (textureType == TextureType::RGBAREPLACEMENT || textureType == TextureType::SRGBREPLACEMENT)
		
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
	
		m_textureMap[tag] = texture;
		texture->InnerSetImage(image);
		return texture;
	}
	else {
		return nullptr;
	}
}


/**
 * Load reads the obj data into a new mesh using C++ combined with c style coding.
 * The result is an indexed mesh for use with glDrawElements.
 * Expects a obj file with following layout v/vt/vn/f eg
 *
 * For example the obj file for a simple plane describes two triangles, based on
 * four vertices, with 4 uv's all having the same vertex normals (NOT FACE NORMALS!)
 *
 * v 10.000000 0.000000 10.000000              //vertex 1
 * v -10.000000 0.000000 10.000000             //vertex 2
 * v 10.000000 0.000000 -10.000000             //vertex 3
 * v -10.000000 0.000000 -10.000000            //vertex 4
 * vt 0.000000 0.000000                        //uv 1
 * vt 1.000000 0.000000                        //uv 2
 * vt 1.000000 1.000000                        //uv 3
 * vt 0.000000 1.000000                        //uv 4
 * vn 0.000000 1.000000 -0.000000              //normal 1 (normal for each vertex is same)
 * s off
 *
 * Using these vertices, uvs and normals we can construct faces, made up of 3 triplets (vertex, uv, normal)
 * f 2/1/1 1/2/1 3/3/1                         //face 1 (triangle 1)
 * f 4/4/1 2/1/1 3/3/1                         //face 2 (triangle 2)
 *
 * So although this is a good format for blender and other tools reading .obj files, this is
 * not an index mechanism that OpenGL supports out of the box.
 * The reason is that OpenGL supports only one indexbuffer, and the value at a certain point in the indexbuffer, eg 3
 * refers to all three other buffers (v, vt, vn) at once,
 * eg if index[0] = 5, opengl will stream vertexBuffer[5], uvBuffer[5], normalBuffer[5] into the shader.
 *
 * So what we have to do after reading the file with all vertices, is construct unique indexes for
 * all pairs that are described by the faces in the object file, eg if you have
 * f 2/1/1 1/2/1 3/3/1                         //face 1 (triangle 1)
 * f 4/4/1 2/1/1 3/3/1                         //face 2 (triangle 2)
 *
 * v/vt/vn[0] will represent 2/1/1
 * v/vt/vn[1] will represent 1/2/1
 * v/vt/vn[2] will represent 3/3/1
 * v/vt/vn[3] will represent 4/4/1
 *
 * and that are all unique pairs, after which our index buffer can contain:
 *
 * 0,1,2,3,0,2
 *
 * So the basic process is, read ALL data into separate arrays, then use the faces to
 * create unique entries in a new set of arrays and create the indexbuffer to go along with it.
 *
 * Note that loading this mesh isn't cached like we do with texturing, this is an exercise left for the students.
 */

Mesh * ResourceManager::LoadMesh(const std::string & path, const std::string & tag)
{
	std::cout << "Loading " << path << "...";

	if (m_meshMap.find(tag) != m_meshMap.end())
	{
		std::cout << "A mesh with that tag is already created" << std::endl;
		throw;
	}

	Mesh* mesh = new Mesh();

	std::ifstream file(path, std::ios::in);

	if (file.is_open()) {
		//these three vectors will contains data as taken from the obj file
		//in the order it is encountered in the object file
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;

		//in addition we create a map to store the triplets found under the f(aces) section in the
		//object file and map them to an index for our index buffer (just number them sequentially
		//as we encounter them and store references to the pack
		std::map <FaceIndexTriplet, unsigned int> mappedTriplets;

		std::string line; // to store each line in
		while (getline(file, line)) {

			// c-type string to store cmd read from obj file (cmd is v, vt, vn, f)
			char cmd[10];
			cmd[0] = 0;

			//get the first string in the line of max 10 chars (c-style)
			sscanf(line.c_str(), "%10s", cmd);

			//note that although the if statements below seem to imply that we can
			//read these different line types (eg vertex, normal, uv) in any order,
			//this is just convenience coding for us (instead of multiple while loops)
			//we assume the obj file to list ALL v lines first, then ALL vt lines,
			//then ALL vn lines and last but not least ALL f lines last

			//so... start processing lines
			//are we reading a vertex line? straightforward copy into local vertices vector
			if (strcmp(cmd, "v") == 0) {
				glm::vec3 vertex;
				sscanf(line.c_str(), "%10s %f %f %f ", cmd, &vertex.x, &vertex.y, &vertex.z);
				vertices.push_back(vertex);

				//or are we reading a normal line? straightforward copy into local normal vector
			}
			else if (strcmp(cmd, "vn") == 0) {
				glm::vec3 normal;
				sscanf(line.c_str(), "%10s %f %f %f ", cmd, &normal.x, &normal.y, &normal.z);
				normals.push_back(normal);

				//or are we reading a uv line? straightforward copy into local uv vector
			}
			else if (strcmp(cmd, "vt") == 0) {
				glm::vec2 uv;
				sscanf(line.c_str(), "%10s %f %f ", cmd, &uv.x, &uv.y);
				uvs.push_back(uv);

				//this is where it gets nasty. After having read all vertices, normals and uvs into
				//their own buffer
			}
			else if (strcmp(cmd, "f") == 0) {

				//an f lines looks like
				//f 2/1/1 1/2/1 3/3/1
				//in other words
				//f v1/u1/n1 v2/u2/n2 v3/u3/n3
				//for each triplet like that we need to check whether we already encountered it
				//and update our administration based on that
				glm::ivec3 vertexIndex;
				glm::ivec3 normalIndex;
				glm::ivec3 uvIndex;
				int count = sscanf(line.c_str(), "%10s %d/%d/%d %d/%d/%d %d/%d/%d", cmd, &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

				//Have we read exactly 10 elements?
				if (count == 10) {

					//process 3 triplets, one for each vertex (which is first element of the triplet)
					for (int i = 0; i < 3; ++i) {
						//create key out of the triplet and check if we already encountered this before
						FaceIndexTriplet triplet(vertexIndex[i], uvIndex[i], normalIndex[i]);
						std::map<FaceIndexTriplet, unsigned int>::iterator found = mappedTriplets.find(triplet);

						//if iterator points at the end, we haven't found it
						if (found == mappedTriplets.end())
						{
							//so create a new index value, and map our triplet to it
							unsigned int index = mappedTriplets.size();
							mappedTriplets[triplet] = index;

							//now record this index
							//mesh->Indices().push_back(index);
							mesh->AddIndex(index);
							//and store the corresponding vertex/normal/uv values into our own buffers
							//note the -1 is required since all values in the f triplets in the .obj file
							//are 1 based, but our vectors are 0 based

							//mesh->Vertices().push_back(vertices[vertexIndex[i] - 1]);
							//mesh->Normals().push_back(normals[normalIndex[i] - 1]);
							//mesh->UVs().push_back(uvs[uvIndex[i] - 1]);
							mesh->AddVertex(vertices[vertexIndex[i] - 1]);
							mesh->AddNormal(normals[normalIndex[i] - 1]);
							mesh->AddUVs(uvs[uvIndex[i] - 1]);

							glm::vec3 v0 = vertices[vertexIndex[0] -1];
							glm::vec3 v1 = vertices[vertexIndex[1] - 1];
							glm::vec3 v2 = vertices[vertexIndex[2] - 1];

							glm::vec2 u0 = uvs[uvIndex[0] - 1];
							glm::vec2 u1 = uvs[uvIndex[1] - 1];
							glm::vec2 u2 = uvs[uvIndex[2] - 1];

							glm::vec3 deltaPos1 = v1 - v0;
							glm::vec3 deltaPos2 = v2 - v0;

							glm::vec2 deltaUV1 = u1 - u0;
							glm::vec2 deltaUV2 = u2 - u0;

							float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
							glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
							glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

							mesh->AddTangent(tangent);
							mesh->AddBiTangent(bitangent);

						}
						else
						{
							//if the key was already present, get the index value for it
							unsigned int index = found->second;
							//and update our index buffer with it

							//mesh->Indices().push_back(index);
							mesh->AddIndex(index);
						}
					}
				}
				else {
					//If we read a different amount, something is wrong
					std::cout << "Error reading obj, needing v,vn,vt" << std::endl;
					delete mesh;
					return NULL;
				}
			}

		}

		file.close();

		std::cout << "Mesh loaded and buffered:" << (mesh->Indices().size() / 3.0f) << " triangles." << std::endl;
		m_meshMap[tag] = mesh;
		return mesh;
	}
	else {
		std::cout << "Could not read " << path << std::endl;
		delete mesh;
		return NULL;
	}
}

Texture * ResourceManager::GetTexture(const std::string & tag)
{
	if (m_textureMap.find(tag) == m_textureMap.end())
	{
		std::cout << "There is no Texture resource with: " << tag << " as a name" << std::endl;

		return nullptr;
		//return GetTexture("ErrorTexture");
	}

	return m_textureMap[tag];
}

Mesh * ResourceManager::GetMesh(const std::string & tag)
{
	if (m_meshMap.find(tag) == m_meshMap.end())
	{
		std::cout << "There is no Mesh resource with: " << tag << " as a name" << std::endl;

		return nullptr;
		//return GetTexture("ErrorTexture");
	}

	return m_meshMap[tag];
}

sf::Texture * ResourceManager::LoadSFMLTexture(const std::string & path, const std::string & tag)
{
	if (m_sfmlTextures.find(tag) != m_sfmlTextures.end())
	{
		std::cout << "A SFML Texture Resource with that tag is already created" << std::endl;
		throw;
	}

	sf::Texture* tex = new sf::Texture();
	if (tex->loadFromFile(path))
	{
		m_sfmlTextures[tag] = tex;
		return tex;
	}
	else
	{
		std::cout << "could not load the sfml texture" << std::endl;
		throw;
	}
}

sf::Texture * ResourceManager::GetSFMLTexture(const std::string & tag)
{
	if (m_sfmlTextures.find(tag) == m_sfmlTextures.end())
	{
		std::cout << "There is no SFML Texture resource with: " << tag << " as a name" << std::endl;

		return nullptr;
		//return GetTexture("ErrorTexture");
	}
	else
	{
		return m_sfmlTextures[tag];
	}
}

AbstractMaterial * ResourceManager::RegisterMaterial(AbstractMaterial * mat, const std::string & tag)
{
	if (mat->IsRegistered() || m_materialMap.find(tag) != m_materialMap.end())
	{
		std::cout << "Material Is already Registered" << std::endl;
		return m_materialMap[tag];
	}
	mat->Register();
	m_materialMap[tag] = mat;
	return mat;
}

AbstractMaterial * ResourceManager::GetMaterial(const std::string & tag)
{
	if (m_materialMap.find(tag) == m_materialMap.end())
	{
		std::cout << "There is no Material resource with: " <<tag<< " as a name"<< std::endl;

		return nullptr;
		//return GetTexture("ErrorTexture");
	}

	return m_materialMap[tag];
}

sf::Music * ResourceManager::LoadMusic(const std::string & path, const std::string & tag)
{
	if (m_musicMap.find(tag) != m_musicMap.end())
	{
		std::cout << "A Music Resource with that tag is already created" << std::endl;
		throw;
	}

	sf::Music* music = new sf::Music();
	music->openFromFile(path);
	m_musicMap[tag] = music;
	return music;
}

sf::Music * ResourceManager::GetMusic(const std::string & tag)
{
	if (m_musicMap.find(tag) == m_musicMap.end())
	{
		std::cout << "There is no Music resource with: " << tag << " as a name" << std::endl;

		return nullptr;
		//return GetTexture("ErrorTexture");
	}

	return m_musicMap[tag];
}

sf::Sound * ResourceManager::LoadSound(const std::string & path, const std::string & tag)
{

	if (m_soundMap.find(tag) != m_soundMap.end())
	{
		std::cout << "A Sound Resource with that tag is already created" << std::endl;
		throw;
	}

	sf::SoundBuffer* buffer = new sf::SoundBuffer();
	buffer->loadFromFile(path);
	m_soundBuffers.push_back(buffer);

	sf::Sound* s = new sf::Sound();

	s->setBuffer(*buffer);
	m_soundMap[tag] = s;
	return s;
}

sf::Sound * ResourceManager::GetSound(const std::string & tag)
{
	if (m_soundMap.find(tag) == m_soundMap.end())
	{
		std::cout << "There is no Sound resource with: " << tag << " as a name" << std::endl;

		return nullptr;
		//return GetTexture("ErrorTexture");
	}

	return m_soundMap[tag];
}

void ResourceManager::LoadResourcesFromLua()
{
	LuaLoadMeshes();
	LuaLoadDiffuseTextures();
	LuaLoadSpecularTexutres();
	LuaLoadEmissionTextures();
	LuaLoadNormalMaps();
	LuaLoadSounds();
	LuaLoadMusics();

	LuaLoadSFMLTextures();
}

void ResourceManager::LuaLoadMeshes()
{
	m_luaProgram->GetGlobalTable("meshes");

	lua_pushnil(m_luaProgram->GetCurrentLuaState());
	lua_gettable(m_luaProgram->GetCurrentLuaState(), -2);

	while (lua_next(m_luaProgram->GetCurrentLuaState(), -2) != 0)
	{

		std::string name = lua_tostring(m_luaProgram->GetCurrentLuaState(), -2);
		std::string path = lua_tostring(m_luaProgram->GetCurrentLuaState(), -1);
		//std::cout << name <<" "<< path<<  std::endl;
		LoadMesh(path, name);
		lua_pop(m_luaProgram->GetCurrentLuaState(), 1);
	}

	m_luaProgram->PopCurrentTable();
}

void ResourceManager::LuaLoadDiffuseTextures()
{
	m_luaProgram->GetGlobalTable("diffuseTextures");

	lua_pushnil(m_luaProgram->GetCurrentLuaState());
	lua_gettable(m_luaProgram->GetCurrentLuaState(), -2);

	while (lua_next(m_luaProgram->GetCurrentLuaState(), -2) != 0)
	{

		std::string name = lua_tostring(m_luaProgram->GetCurrentLuaState(), -2);
		std::string path = lua_tostring(m_luaProgram->GetCurrentLuaState(), -1);
		//std::cout << name <<" "<< path<<  std::endl;
		LoadTexture(path, name, TextureType::DIFFUSE);
		lua_pop(m_luaProgram->GetCurrentLuaState(), 1);
	}

	m_luaProgram->PopCurrentTable();
}

void ResourceManager::LuaLoadSpecularTexutres()
{
	m_luaProgram->GetGlobalTable("specularTextures");

	lua_pushnil(m_luaProgram->GetCurrentLuaState());
	lua_gettable(m_luaProgram->GetCurrentLuaState(), -2);

	while (lua_next(m_luaProgram->GetCurrentLuaState(), -2) != 0)
	{

		std::string name = lua_tostring(m_luaProgram->GetCurrentLuaState(), -2);
		std::string path = lua_tostring(m_luaProgram->GetCurrentLuaState(), -1);
		//std::cout << name <<" "<< path<<  std::endl;
		LoadTexture(path, name, TextureType::SPECULAR);
		lua_pop(m_luaProgram->GetCurrentLuaState(), 1);
	}

	m_luaProgram->PopCurrentTable();
}

void ResourceManager::LuaLoadEmissionTextures()
{
	m_luaProgram->GetGlobalTable("emissionTextures");

	lua_pushnil(m_luaProgram->GetCurrentLuaState());
	lua_gettable(m_luaProgram->GetCurrentLuaState(), -2);

	while (lua_next(m_luaProgram->GetCurrentLuaState(), -2) != 0)
	{

		std::string name = lua_tostring(m_luaProgram->GetCurrentLuaState(), -2);
		std::string path = lua_tostring(m_luaProgram->GetCurrentLuaState(), -1);
		//std::cout << name <<" "<< path<<  std::endl;
		LoadTexture(path, name, TextureType::EMISSION);
		lua_pop(m_luaProgram->GetCurrentLuaState(), 1);
	}

	m_luaProgram->PopCurrentTable();
}

void ResourceManager::LuaLoadNormalMaps()
{
	m_luaProgram->GetGlobalTable("normalMapTextures");

	lua_pushnil(m_luaProgram->GetCurrentLuaState());
	lua_gettable(m_luaProgram->GetCurrentLuaState(), -2);

	while (lua_next(m_luaProgram->GetCurrentLuaState(), -2) != 0)
	{

		std::string name = lua_tostring(m_luaProgram->GetCurrentLuaState(), -2);
		std::string path = lua_tostring(m_luaProgram->GetCurrentLuaState(), -1);
		//std::cout << name <<" "<< path<<  std::endl;
		LoadTexture(path, name, TextureType::NORMAL);
		lua_pop(m_luaProgram->GetCurrentLuaState(), 1);
	}

	m_luaProgram->PopCurrentTable();
}

void ResourceManager::LuaLoadSFMLTextures()
{
	m_luaProgram->GetGlobalTable("sfmlTextures");

	lua_pushnil(m_luaProgram->GetCurrentLuaState());
	lua_gettable(m_luaProgram->GetCurrentLuaState(), -2);

	while (lua_next(m_luaProgram->GetCurrentLuaState(), -2) != 0)
	{

		std::string name = lua_tostring(m_luaProgram->GetCurrentLuaState(), -2);
		std::string path = lua_tostring(m_luaProgram->GetCurrentLuaState(), -1);
		//std::cout << name <<" "<< path<<  std::endl;
		LoadSFMLTexture(path, name);
		lua_pop(m_luaProgram->GetCurrentLuaState(), 1);
	}

	m_luaProgram->PopCurrentTable();
}

void ResourceManager::LuaLoadSounds()
{
	m_luaProgram->GetGlobalTable("sounds");

	lua_pushnil(m_luaProgram->GetCurrentLuaState());
	lua_gettable(m_luaProgram->GetCurrentLuaState(), -2);

	while (lua_next(m_luaProgram->GetCurrentLuaState(), -2) != 0)
	{

		std::string name = lua_tostring(m_luaProgram->GetCurrentLuaState(), -2);
		std::string path = lua_tostring(m_luaProgram->GetCurrentLuaState(), -1);
		//std::cout << name <<" "<< path<<  std::endl;
		LoadSound(path, name);
		lua_pop(m_luaProgram->GetCurrentLuaState(), 1);
	}

	m_luaProgram->PopCurrentTable();
}

void ResourceManager::LuaLoadMusics()
{
	m_luaProgram->GetGlobalTable("musics");

	lua_pushnil(m_luaProgram->GetCurrentLuaState());
	lua_gettable(m_luaProgram->GetCurrentLuaState(), -2);

	while (lua_next(m_luaProgram->GetCurrentLuaState(), -2) != 0)
	{

		std::string name = lua_tostring(m_luaProgram->GetCurrentLuaState(), -2);
		std::string path = lua_tostring(m_luaProgram->GetCurrentLuaState(), -1);
		//std::cout << name <<" "<< path<<  std::endl;
		LoadMusic(path, name);
		lua_pop(m_luaProgram->GetCurrentLuaState(), 1);
	}

	m_luaProgram->PopCurrentTable();
}
