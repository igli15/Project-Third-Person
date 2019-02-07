#include <iostream>
#include <map>
#include <string>
#include <fstream>

#include "mge/core/Mesh.hpp"

Mesh::Mesh(): _vertices(), _normals(), _uvs(), _indices()
{
	//ctor
}

Mesh::~Mesh()
{
	//dtor
}


std::vector<glm::vec3> Mesh::Vertices() 
{
	return _vertices;
}

std::vector<glm::vec3> Mesh::Normals() 
{
	return _normals;
}

std::vector<glm::vec2> Mesh::UVs() 
{
	return _uvs;
}

std::vector<unsigned> Mesh::Indices() 
{
	return _indices;
}

void Mesh::AddVertex(glm::vec3 v)
{
	_vertices.push_back(v);
}

void Mesh::AddNormal(glm::vec3 n)
{
	_normals.push_back(n);
}

void Mesh::AddUVs(glm::vec2 uv)
{
	_uvs.push_back(uv);
}

void Mesh::AddIndex(unsigned i)
{
	_indices.push_back(i);
}



