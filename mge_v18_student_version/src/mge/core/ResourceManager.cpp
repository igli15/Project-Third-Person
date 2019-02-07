#include "ResourceManager.h"
#include "SFML/Graphics.hpp"
 
#include <iostream>
#include <map>
#include <string>
#include <fstream>

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}


Texture * ResourceManager::LoadTexture(const std::string & path, const std::string & tag, TextureType textureType)
{
	// load from file and store in cache
	sf::Image image;
	if (image.loadFromFile(path)) {
		//normal image 0,0 is top left, but opengl considers 0,0 to be bottom left, so we flip the image internally
		image.flipVertically();
		//create a wrapper for the id (texture is nothing more than that) and
		//load corresponding data into opengl using this id
		Texture * texture = new Texture();

		glBindTexture(GL_TEXTURE_2D, texture->getId());

		//If we want specular / normals maps we still have to use rgba instead of SRGB

		if (textureType == TextureType::SPECULAR)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
		}
		else if (textureType == TextureType::DIFFUSE)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
	
		m_textureMap[tag] = texture;

		return texture;
	}
	else {
		return nullptr;
	}
}

Mesh * ResourceManager::LoadMesh(const std::string & path, const std::string & tag)
{
	std::cout << "Loading " << path << "...";

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
		std::cout << "There is no Texture resource with that name!" << std::endl;

		return nullptr;
		//return GetTexture("ErrorTexture");
	}

	return m_textureMap[tag];
}

Mesh * ResourceManager::GetMesh(const std::string & tag)
{
	if (m_meshMap.find(tag) == m_meshMap.end())
	{
		std::cout << "There is no Mesh resource with that name!" << std::endl;

		return nullptr;
		//return GetTexture("ErrorTexture");
	}

	return m_meshMap[tag];
}
