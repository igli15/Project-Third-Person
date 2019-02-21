#include "MainWorld.h"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "components/KeyMoveComponent.h"
#include "components/RotatingComponent.h"
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
#include "MainGame.h"
#include "lua.h"
#include"mge/components/AudioSource.h"
#include "mge\components\UISpriteRenderer.h"


#include "rapidxml/rapidxml.hpp"
#include <fstream>
#include <streambuf>

MainWorld::MainWorld()
{

}


void MainWorld::Initialize()
{
	Mesh* planeMeshDefault = AbstractGame::Instance()->GetResourceManager()->GetMesh("planeMesh");
	Mesh* cubeMesh = AbstractGame::Instance()->GetResourceManager()->GetMesh("cubeMesh");;
	Mesh* Car = AbstractGame::Instance()->GetResourceManager()->GetMesh("carMesh");;
	Mesh* gunMesh = AbstractGame::Instance()->GetResourceManager()->GetMesh("testMesh");;

	AbstractMaterial* brickMat = AbstractGame::Instance()->GetResourceManager()->GetMaterial("brickMat");
	ColorMaterial* planeMat = dynamic_cast<ColorMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("planeMat"));
	planeMat->SetShineness(126);
	planeMat->SetDiffuseColor(glm::vec3(0.13f, 0.54f, 0.130f));
	ColorMaterial* lightMat = dynamic_cast<ColorMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("lightMat"));
	lightMat->SetDiffuseColor(glm::vec3(1, 1, 0.8f));

	TextureMaterial* containerMat = dynamic_cast<TextureMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("containerMat"));
	TextureMaterial* radioMat = dynamic_cast<TextureMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("stuffMat"));

	Camera* camera = Instantiate<Camera>();
	camera->transform->SetLocalPosition(glm::vec3(0, 15, 10));
	camera->transform->Rotate(glm::radians(-65.0f), glm::vec3(1, 0, 0));
	camera->GetCameraComponent()->SetFOV(60); //Set Camera Properties via its component
	_world->setMainCamera(camera->GetCameraComponent());


	
	GameObject* cube2 = _world->Instantiate<GameObject>();
	cube2->transform->SetLocalPosition(glm::vec3(0.5, 0.0f, 4));
	cube2->SetMeshRenderer(cube2->AddComponent<MeshRenderer>());
	cube2->GetMeshRenderer()->SetMesh(gunMesh);
	cube2->setMaterial(radioMat);
	cube2->transform->Scale(glm::vec3(1.0f,1.0f, 1.0f));
	cube2->AddComponent<KeyMoveComponent>();
	//radioMat->SetShininess(256);
	

	GameObject* canvas = _world->Instantiate<GameObject>();
	canvas->AddComponent<CanvasComponent>();
	canvas->Awake();

	/*
	GameObject* sprite = _world->Instantiate<GameObject>();
	sprite->AddComponent<UISpriteRenderer>()->ApplyTexture(AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("brickTex"));
	sprite->Awake();

	*/

	/*cube2->AddComponent<AudioSource>()->SetMusic(AbstractGame::Instance()->GetResourceManager()->GetMusic("expmusic"));
	cube2->GetComponent<AudioSource>()->PlayMusic();
	cube2->GetComponent<AudioSource>()->PlayOneShotSound("cannonShot");
	*/
	
	//cube2->setBehaviour(new KeysBehaviour());


	/*
	GameObject* cube = _world->Instantiate<GameObject>();
	cube->transform->SetLocalPosition(glm::vec3(0, 16, 19));
	//cube->transform->Rotate(glm::radians(45.0f),glm::vec3(1, 0,1));
	cube->SetMeshRenderer(cube->AddComponent<MeshRenderer>());
	cube->GetMeshRenderer()->SetMesh(cubeMesh);
	cube->AddComponent<RotatingComponent>();
	cube->setMaterial(containerMat);
	*/

	/*
	GameObject* goodBoy = _world->Instantiate<GameObject>();
	goodBoy->transform->SetLocalPosition(glm::vec3(0, 20, 21));
	//goodBoy->transform->Scale(glm::vec3(2,5,2));
	goodBoy->SetMeshRenderer(goodBoy->AddComponent<MeshRenderer>());
	goodBoy->GetMeshRenderer()->SetMesh(AbstractGame::Instance()->GetResourceManager()->GetMesh("goodBoyMesh"));
	goodBoy->AddComponent<RotatingComponent>();

	goodBoy->setMaterial(AbstractGame::Instance()->GetResourceManager()->GetMaterial("goodBoyMat"));
	*/

	Light* l = _world->Instantiate<Light>();
	l->transform->SetLocalPosition(glm::vec3(0, 19,19));
	l->transform->Rotate(glm::radians(90.0f), glm::vec3(1, 0, 0));
	l->transform->Rotate(glm::radians(45.0f), glm::vec3(0, 1, 1));
	l->GetLightComponent()->SetType(LightType::POINT);
	l->GetLightComponent()->SetIntensity(1.0f);
	l->GetLightComponent()->SetColor(glm::vec3(1, 1, 0.95f));
	l->GetLightComponent()->SetSpecularContribution(1.0f);
	l->GetLightComponent()->SetAttenuationConstants(glm::vec3(1, 0.7f, 1.8f));
	l->SetMeshRenderer(l->AddComponent<MeshRenderer>());
	l->GetMeshRenderer()->SetMesh(cubeMesh);
	l->setMaterial(lightMat);
	l->transform->Scale(glm::vec3(0.2f, 0.2f, 0.2f));

	Light* l2 = _world->Instantiate<Light>();
	l2->transform->SetLocalPosition(glm::vec3(2, 2, 0));
	l2->transform->Rotate(glm::radians(90.0f), glm::vec3(1, 0, 0));
	l2->transform->Rotate(glm::radians(45.0f), glm::vec3(0, 1, 0));
	l2->GetLightComponent()->SetType(LightType::POINT);
	l2->GetLightComponent()->SetColor(glm::vec3(1, 1, 0.8f));
	l2->GetLightComponent()->SetSpecularContribution(0.4f);
	l2->GetLightComponent()->SetAttenuationConstants(glm::vec3(1, 0.7f, 1.8f));
	l2->SetMeshRenderer(l2->AddComponent<MeshRenderer>());
	l2->GetMeshRenderer()->SetMesh(cubeMesh);
	l2->setMaterial(lightMat);
	l2->transform->Scale(glm::vec3(0.2f, 0.2f, 0.2f));

	//l2->Destroy();

}

MainWorld::~MainWorld()
{

}
