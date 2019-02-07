#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include "../components/CameraComponent.h"
#include "Mesh.hpp"
#include "World.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "../components/MeshRenderer.h"

Renderer::Renderer():debug(false)
{
    //make sure we test the depthbuffer
	glEnable(GL_DEPTH_TEST);

	//tell opengl which vertex winding is considered to be front facing
	glFrontFace(GL_CCW);

	//tell opengl to enable face culling for the back faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//set the default blend mode aka dark magic:
	//https://www.opengl.org/sdk/docs/man/html/glBlendFunc.xhtml
    //https://www.opengl.org/wiki/Blending
    //http://www.informit.com/articles/article.aspx?p=1616796&seqNum=5
    //http://www.andersriggelsen.dk/glblendfunc.php
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor((float)0x2d / 0xff, (float)0x6b / 0xff, (float)0xce / 0xff, 1.0f);
}

Renderer::~Renderer()
{
}

void Renderer::setClearColor(GLbyte pR, GLbyte pG, GLbyte pB) {
	glClearColor((float)pR / 0xff, (float)pG / 0xff, (float)pB / 0xff, 1.0f);
}

void Renderer::render(World* pWorld) {
	render(pWorld, pWorld, nullptr, pWorld->getMainCamera(), true);
}

void Renderer::render(World* pWorld, GameObject* pGameObject, AbstractMaterial* pMaterial, Camera* pCamera, bool pRecursive)
{
	render(pWorld, pGameObject, pMaterial, pGameObject->transform->WorldTransform(), glm::inverse(pCamera->transform->WorldTransform()), pCamera->GetCameraComponent()->GetProjection(), pRecursive);
}

void Renderer::render(World* pWorld, GameObject* pGameObject, AbstractMaterial* pMaterial, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix, bool pRecursive) {
	renderSelf(pWorld, pGameObject, pMaterial == nullptr?pGameObject->getMaterial():pMaterial, pModelMatrix, pViewMatrix, pProjectionMatrix);
	if (pRecursive) renderChildren(pWorld, pGameObject, pMaterial, pModelMatrix, pViewMatrix, pProjectionMatrix, pRecursive);
}

void Renderer::renderSelf(World* pWorld, GameObject* pGameObject, AbstractMaterial* pMaterial, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	render(pWorld, pGameObject->GetMeshRenderer(), pMaterial, pModelMatrix, pViewMatrix, pProjectionMatrix);
	if (debug) renderMeshDebugInfo(pGameObject->GetMeshRenderer(), pModelMatrix, pViewMatrix, pProjectionMatrix);
}

void Renderer::renderChildren(World* pWorld, GameObject* pGameObject, AbstractMaterial* pMaterial, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix, bool pRecursive) {
	int childCount = pGameObject->getChildCount();
	if (childCount < 1) return;

	//note that with a loop like this, deleting children during rendering is not a good idea :')
	GameObject* child = 0;
	for (int i = childCount -1 ; i >= 0; --i) {
		child = pGameObject->getChildAt(i);
		render(pWorld, child, pMaterial, pModelMatrix * child->transform->LocalTransform(), pViewMatrix, pProjectionMatrix, pRecursive);
	}
}

void Renderer::render(World* pWorld, MeshRenderer* meshRenderer, AbstractMaterial* pMaterial, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	if (meshRenderer != nullptr && pMaterial != nullptr) pMaterial->render(pWorld, meshRenderer, pModelMatrix, pViewMatrix, pProjectionMatrix);
}

void Renderer::renderMeshDebugInfo(MeshRenderer* meshRenderer, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	if (meshRenderer != nullptr) meshRenderer->DrawMeshDebugInfo(pModelMatrix, pViewMatrix, pProjectionMatrix);
}

