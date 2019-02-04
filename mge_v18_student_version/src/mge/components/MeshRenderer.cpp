#include "MeshRenderer.h"

#include "mge/core/GameObject.hpp"


MeshRenderer::MeshRenderer()
{
	
}


MeshRenderer::~MeshRenderer()
{
	std::cout << "mesh is destroyed" << std::endl;
	m_currentMesh = nullptr;
}

void MeshRenderer::Awake()
{
	m_gameObject->SetMeshRenderer(this);
}

void MeshRenderer::SetMesh(Mesh * mesh)
{
	m_currentMesh = mesh;
	BufferMesh();
}

void MeshRenderer::StreamToOpenGL(GLint pVerticesAttrib, GLint pNormalsAttrib, GLint pUVsAttrib)
{
	if (m_currentMesh == nullptr)
	{
		std::cout << "No Mesh is Assigned to the Mesh Renderer" << std::endl;
		return;
	}

	//std::cout << "buffered" << std::endl;

	if (pVerticesAttrib != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
		glEnableVertexAttribArray(pVerticesAttrib);
		glVertexAttribPointer(pVerticesAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (pNormalsAttrib != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, m_normalBufferId);
		glEnableVertexAttribArray(pNormalsAttrib);
		glVertexAttribPointer(pNormalsAttrib, 3, GL_FLOAT, GL_TRUE, 0, 0);
	}

	if (pUVsAttrib != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, m_uvBufferId);
		glEnableVertexAttribArray(pUVsAttrib);
		glVertexAttribPointer(pUVsAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);

	glDrawElements(GL_TRIANGLES, m_currentMesh->Indices().size(), GL_UNSIGNED_INT, (GLvoid*)0);

	// no current buffer, to avoid mishaps, very important for performance

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//fix for serious performance issue
	if (pUVsAttrib != -1) glDisableVertexAttribArray(pUVsAttrib);
	if (pNormalsAttrib != -1) glDisableVertexAttribArray(pNormalsAttrib);
	if (pVerticesAttrib != -1) glDisableVertexAttribArray(pVerticesAttrib);
}

void MeshRenderer::DrawMeshDebugInfo(const glm::mat4 & pModelMatrix, const glm::mat4 & pViewMatrix, const glm::mat4 & pProjectionMatrix)
{
	if (m_currentMesh == nullptr)
	{
		std::cout << "No Mesh is Assigned to the Mesh Renderer" << std::endl;
		return;
	}

	glUseProgram(0);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(pProjectionMatrix));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(pViewMatrix * pModelMatrix));

    glBegin(GL_LINES);
    //for each index draw the normal starting at the corresponding vertex
    for (size_t i=0; i<m_currentMesh->Indices().size(); i++){
        //draw normal for vertex
        if (true) {
            //now get normal end
            glm::vec3 normal = m_currentMesh->Normals()[m_currentMesh->Indices()[i]];
            glColor3fv(glm::value_ptr(normal));

            glm::vec3 normalStart = m_currentMesh->Vertices()[m_currentMesh->Indices()[i]];
            glVertex3fv(glm::value_ptr(normalStart));
            glm::vec3 normalEnd = normalStart + normal*0.2f;
            glVertex3fv(glm::value_ptr(normalEnd));
        }

    }
    glEnd();
}


void MeshRenderer::BufferMesh()
{
	glGenBuffers(1, &m_indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_currentMesh->Indices().size() * sizeof(unsigned int), &m_currentMesh->Indices()[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_currentMesh->Vertices().size() * sizeof(glm::vec3), &m_currentMesh->Vertices()[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_normalBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_normalBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_currentMesh->Normals().size() * sizeof(glm::vec3), &m_currentMesh->Normals()[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_uvBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_currentMesh->UVs().size() * sizeof(glm::vec2), &m_currentMesh->UVs()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
