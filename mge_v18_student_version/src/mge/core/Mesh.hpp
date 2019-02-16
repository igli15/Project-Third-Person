#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <GL/glew.h>
#include "glm.hpp"
#include "Component.h"


class World;

/**
 * A mesh represents an .OBJ file. It knows how it is constructed, how its data should be buffered to OpenGL
 * and how it should be streamed to OpenGL
 */
class Mesh
{
	public:
		Mesh();
		virtual ~Mesh();

		std::vector<glm::vec3> Vertices();
		std::vector<glm::vec3> Normals() ;
		std::vector<glm::vec2> UVs() ;

		std::vector<glm::vec3> Tangents();
		std::vector<glm::vec3> BiTangents();

		std::vector<unsigned> Indices() ;

		void AddVertex(glm::vec3 v);
		void AddNormal(glm::vec3 n);
		void AddUVs(glm::vec2 uv);
		void AddIndex(unsigned i);

		void AddTangent(glm::vec3 t);
		void AddBiTangent(glm::vec3 b);

	protected:

	    //the actual data
		std::vector<glm::vec3> _vertices;       //vec3 with 3d coords for all vertices
		std::vector<glm::vec3> _normals;        //vec3 with 3d normal data
		std::vector<glm::vec2> _uvs;            //vec2 for uv

		std::vector<glm::vec3> m_tangents;
		std::vector<glm::vec3> m_biTangents;

		//references to the vertices/normals & uvs in previous vectors
		std::vector<unsigned> _indices;


};

//Please read the "load" function documentation on the .obj file format first.
		//FaceVertexTriplet  is a helper class for loading and converting to obj file to
		//indexed arrays.
		//If we list all the unique v/uv/vn triplets under the faces
		//section in an object file sequentially and assign them a number
		//it would be a map of FaceVertexTriplet. Each FaceVertexTriplet refers
		//to an index with the originally loaded vertex list, normal list and uv list
		//and is only used during conversion (unpacking) of the facevertextriplet list
		//to a format that OpenGL can handle.
		//So for a vertex index a FaceVertexTriplet contains the index for uv and n as well.
class FaceIndexTriplet {
public:
	unsigned v; //vertex
	unsigned uv;//uv
	unsigned n; //normal
	FaceIndexTriplet(unsigned pV, unsigned pUV, unsigned pN)
		: v(pV), uv(pUV), n(pN) {
	}
	//needed for use as key in map
	bool operator<(const FaceIndexTriplet other) const {
		return memcmp((void*)this, (void*)&other, sizeof(FaceIndexTriplet)) > 0;
	}
};

#endif // MESH_HPP
