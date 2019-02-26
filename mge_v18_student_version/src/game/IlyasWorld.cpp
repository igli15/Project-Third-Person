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
#include "mge/components/CircleCollider.h"
#include "mge/components/RectangleCollider.h"
#include "mge/components//RigidBody.h"
#include "PhysicsTestObject.h"
#include "Player.h"

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
	camera->transform->SetLocalPosition(glm::vec3(5, 40, 0));
	camera->transform->Rotate(glm::radians(-90.0f), glm::vec3(1, 0, 0));
	camera->GetCameraComponent()->SetFOV(60); //Set Camera Properties via its component
	_world->setMainCamera(camera->GetCameraComponent());


	GameObject* plane = _world->Instantiate<GameObject>();
	plane->transform->SetLocalPosition(glm::vec3(0, -1, 0));
	plane->SetMeshRenderer(plane->AddComponent<MeshRenderer>());
	plane->GetMeshRenderer()->SetMesh(planeMeshDefault);
	plane->setMaterial(planeMat);
	plane->transform->Scale(glm::vec3(50, 50, 50));

	Player* player1 = _world->Instantiate<Player>();
	player1->transform->Translate(glm::vec3(1, 0, 4));
	player1->GetMeshRenderer()->SetMesh(cylinderMesh);
	player1->setMaterial(carMat);
	player1->SetPlayerNumber(1);

	Player* player2 = _world->Instantiate<Player>();
	player2->transform->Translate(glm::vec3(1, 0, 0));
	player2->GetMeshRenderer()->SetMesh(cylinderMesh);
	player2->setMaterial(carMat);
	player1->SetPlayerNumber(2);
	/*
	//Test object 2
	GameObject* cylinder2 = _world->Instantiate<GameObject>();
	cylinder2->transform->SetLocalPosition(glm::vec3(10, 0, 3));
	cylinder2->SetMeshRenderer(cylinder2->AddComponent<MeshRenderer>());
	cylinder2->GetMeshRenderer()->SetMesh(cylinderMesh);
	cylinder2->setMaterial(brickMat);
	cylinder2->transform->Scale(glm::vec3(1, 2, 1));
	cylinder2->AddComponent<CircleCollider>();
	cylinder2->Awake();
	cylinder2->GetComponent<CircleCollider>()->SetCollisionLayerTag("DIF");
	//cylinder2->GetComponent<CircleCollider>()->AddCollisionFilterTag("test_cylender2");
	
	//Test object 3
	GameObject* cylinder3 = _world->Instantiate<GameObject>();
	cylinder3->transform->SetLocalPosition(glm::vec3(10, 0, -5));
	cylinder3->SetMeshRenderer(cylinder3->AddComponent<MeshRenderer>());
	cylinder3->GetMeshRenderer()->SetMesh(cylinderMesh);
	cylinder3->setMaterial(brickMat);
	cylinder3->transform->Scale(glm::vec3(1, 4, 1));
	cylinder3->AddComponent<CircleCollider>();
	cylinder3->Awake();
	cylinder3->GetComponent<CircleCollider>()->SetCollisionLayerTag("DIF");
	

	/*GameObject* cube1 = _world->Instantiate<GameObject>();
	cube1->transform->SetLocalPosition(glm::vec3(10, 0, -5));
	cube1->SetMeshRenderer(cube1->AddComponent<MeshRenderer>());
	cube1->GetMeshRenderer()->SetMesh(cubeMesh);
	cube1->setMaterial(brickMat);
	cube1->transform->Scale(glm::vec3(1, 1, 1));
	cube1->AddComponent<RectangleCollider>();
	cube1->AddComponent<KeyMoveComponent>();
	cube1->Awake();
	*/
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			GameObject* cube2 = _world->Instantiate<GameObject>();
			cube2->transform->SetLocalPosition(glm::vec3(-20+8* i, 0,20 -8*j));
			cube2->SetMeshRenderer(cube2->AddComponent<MeshRenderer>());
			cube2->GetMeshRenderer()->SetMesh(cubeMesh);
			cube2->setMaterial(brickMat);
			cube2->transform->Scale(glm::vec3(1, 1, 1));
			cube2->AddComponent<RectangleCollider>();
			cube2->Awake();

			cube2->GetComponent<RectangleCollider>()->SetCollisionLayerTag("walls");
		}
	}

	
	/*
	GameObject* cube3 = _world->Instantiate<GameObject>();
	cube3->transform->SetLocalPosition(glm::vec3(2, 0,4));
	cube3->SetMeshRenderer(cube3->AddComponent<MeshRenderer>());
	cube3->GetMeshRenderer()->SetMesh(cubeMesh);
	cube3->setMaterial(brickMat);
	cube3->transform->Scale(glm::vec3(1, 1, 1));
	cube3->AddComponent<RectangleCollider>();
	cube3->Awake();


	GameObject* cube4 = _world->Instantiate<GameObject>();
	cube4->transform->SetLocalPosition(glm::vec3(-1, 0,4));
	cube4->SetMeshRenderer(cube4->AddComponent<MeshRenderer>());
	cube4->GetMeshRenderer()->SetMesh(cubeMesh);
	cube4->setMaterial(brickMat);
	cube4->transform->Scale(glm::vec3(1, 1, 1));
	cube4->AddComponent<RectangleCollider>();
	cube4->Awake(); */

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
