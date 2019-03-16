#pragma once
#include "../core/Component.h"
#include "../core/Mesh.hpp"

class MeshRenderer : public Component
{
public:
	MeshRenderer();
	virtual ~MeshRenderer();

	void Awake() override;
	void SetMesh(Mesh* mesh);
	void StreamToOpenGL(GLint pVerticesAttrib, GLint pNormalsAttrib, GLint pUVsAttrib, GLint pTangentsAttrib = -1, GLint pBiTangentsAttrib = -1);
	void DrawMeshDebugInfo(const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix);
	
private:

	void BufferMesh();

	Mesh* m_currentMesh = nullptr;
	

	//OpenGL requirements

	GLuint m_indexBufferId;
	GLuint m_vertexBufferId;
	GLuint m_normalBufferId;
	GLuint m_uvBufferId;

	GLuint m_tangentBufferId;
	GLuint m_biTangentBufferId;

};

