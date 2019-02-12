#include "IlyasWorld.h"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "game/components/KeyMoveComponent.h"
#include "game/components/RotatingComponent.h"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/World.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/test/TestComponent.h"
#include "mge/components/CameraComponent.h"
#include "mge/core/Light.hpp"
#include "mge/components/LightComponent.h"
#include "mge/core/WorldManager.h"
#include "mge/core/ResourceManager.h"
#include "game/MainGame.h"
#include "mge/components/SphereCollider.h"

IlyasWorld::IlyasWorld()
{

}


void IlyasWorld::Initialize()
{
	Mesh* planeMeshDefault = AbstractGame::Instance()->GetResourceManager()->GetMesh("planeMesh");
	Mesh* cubeMesh = AbstractGame::Instance()->GetResourceManager()->GetMesh("cubeMesh");;
	Mesh* Car = AbstractGame::Instance()->GetResourceManager()->GetMesh("carMesh");;
	Mesh* modelMesh = AbstractGame::Instance()->GetResourceManager()->GetMesh("jeepMesh");;
	Mesh* gunMesh = AbstractGame::Instance()->GetResourceManager()->GetMesh("testMesh");;
	Mesh* cylinderMesh= AbstractGame::Instance()->GetResourceManager()->GetMesh("cylinderMesh");;

	AbstractMaterial* brickMat = AbstractGame::Instance()->GetResourceManager()->GetMaterial("brickMat");
	TextureMaterial* carMat = dynamic_cast<TextureMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("carMat"));
	AbstractMaterial* modelMat = (AbstractGame::Instance()->GetResourceManager()->GetMaterial("modelMat"));
	ColorMaterial* planeMat = dynamic_cast<ColorMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("planeMat"));
	planeMat->SetShineness(126);
	planeMat->SetDiffuseColor(glm::vec3(0.13f, 0.54f, 0.130f));
	ColorMaterial* lightMat = dynamic_cast<ColorMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("lightMat"));
	lightMat->SetDiffuseColor(glm::vec3(1, 1, 0.8f));

	TextureMaterial* containerMat = dynamic_cast<TextureMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("containerMat"));
	TextureMaterial* radioMat = dynamic_cast<TextureMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("stuffMat"));

	Camera* camera = _world->Instantiate<Camera>();
	camera->transform->SetLocalPosition(glm::vec3(0, 6, 20));
	camera->transform->Rotate(glm::radians(-20.0f), glm::vec3(1, 0, 0));
	camera->GetCameraComponent()->SetFOV(60); //Set Camera Properties via its component
	_world->setMainCamera(camera);


	GameObject* plane = _world->Instantiate<GameObject>();
	plane->transform->SetLocalPosition(glm::vec3(0, -1, 0));
	plane->SetMeshRenderer(plane->AddComponent<MeshRenderer>());
	plane->GetMeshRenderer()->SetMesh(planeMeshDefault);
	plane->setMaterial(planeMat);
	plane->transform->Scale(glm::vec3(50, 50, 50));

	//TEST object1 
	GameObject* cylinder1 = _world->Instantiate<GameObject>();
	cylinder1->transform->SetLocalPosition(glm::vec3(5, 0, 0));
	cylinder1->SetMeshRenderer(cylinder1->AddComponent<MeshRenderer>());
	cylinder1->GetMeshRenderer()->SetMesh(cylinderMesh);
	cylinder1->setMaterial(brickMat);
	cylinder1->transform->Scale(glm::vec3(1 ,1 ,1));
	cylinder1->AddComponent<KeyMoveComponent>();
	cylinder1->AddComponent<SphereCollider>();

	//Test object 2
	GameObject* cylinder2 = _world->Instantiate<GameObject>();
	cylinder2->transform->SetLocalPosition(glm::vec3(10, 0, 0));
	cylinder2->SetMeshRenderer(cylinder1->AddComponent<MeshRenderer>());
	cylinder2->GetMeshRenderer()->SetMesh(cylinderMesh);
	cylinder2->setMaterial(brickMat);
	cylinder2->transform->Scale(glm::vec3(1, 1, 1));
	cylinder1->AddComponent<SphereCollider>();

	Light* l = _world->Instantiate<Light>();
	l->transform->SetLocalPosition(glm::vec3(-2, 2, 0));
	l->transform->Rotate(glm::radians(90.0f), glm::vec3(1, 0, 0));
	l->transform->Rotate(glm::radians(45.0f), glm::vec3(0, 1, 0));
	l->GetLightComponent()->SetType(LightType::DIRECTIONAL);
	l->GetLightComponent()->SetIntensity(1.0f);
	l->GetLightComponent()->SetColor(glm::vec3(1, 1, 0.95f));
	l->GetLightComponent()->SetSpecularContribution(1.0f);
	l->GetLightComponent()->SetAttenuationConstants(glm::vec3(1, 0.7f, 1.8f));
	l->SetMeshRenderer(l->AddComponent<MeshRenderer>());
	l->GetMeshRenderer()->SetMesh(cubeMesh);
	l->setMaterial(lightMat);
	l->transform->Scale(glm::vec3(0.2f, 0.2f, 0.2f));
}

IlyasWorld::~IlyasWorld()
{

}
