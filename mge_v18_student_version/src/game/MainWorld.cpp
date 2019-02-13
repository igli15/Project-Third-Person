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

MainWorld::MainWorld()
{

}


void MainWorld::Initialize()
{
	Mesh* planeMeshDefault = AbstractGame::Instance()->GetResourceManager()->GetMesh("planeMesh");
	Mesh* cubeMesh = AbstractGame::Instance()->GetResourceManager()->GetMesh("cubeMesh");;
	Mesh* Car = AbstractGame::Instance()->GetResourceManager()->GetMesh("carMesh");;
	Mesh* modelMesh = AbstractGame::Instance()->GetResourceManager()->GetMesh("jeepMesh");;
	Mesh* gunMesh = AbstractGame::Instance()->GetResourceManager()->GetMesh("testMesh");;

	AbstractMaterial* brickMat = AbstractGame::Instance()->GetResourceManager()->GetMaterial("brickMat");
	TextureMaterial* carMat =  dynamic_cast<TextureMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("carMat"));
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

	//GameObject* car = _world->Instantiate<GameObject>();
	//car->transform->SetLocalPosition(glm::vec3(0,0.2f,0));
	//car->SetMeshRenderer(car->AddComponent<MeshRenderer>());
	//car->GetMeshRenderer()->SetMesh(Car);
	//car->setMaterial(carMat);
	//car->transform->Scale(glm::vec3(1, 1, 1));

	//GameObject* model = _world->Instantiate<GameObject>();
	//model->transform->SetLocalPosition(glm::vec3(-6, 0.2, 0));
	//model->SetMeshRenderer(model->AddComponent<MeshRenderer>());
	//model->GetMeshRenderer()->SetMesh(modelMesh);
	//model->setMaterial(modelMat);
	//model->transform->Scale(glm::vec3(1, 1, 1));
	//model->setBehaviour(new RotatingBehaviour());

	//GameObject* cube = _world->Instantiate<GameObject>();
	//cube->transform->SetLocalPosition(glm::vec3(5, 0.2f, 0));
	//cube->SetMeshRenderer(cube->AddComponent<MeshRenderer>());
	//cube->GetMeshRenderer()->SetMesh(cubeMesh);
	//cube->setMaterial(containerMat);
	//cube->transform->Scale(glm::vec3(1, 1, 1));
	//cube->setBehaviour(new RotatingBehaviour());

	GameObject* cube2 = _world->Instantiate<GameObject>();
	cube2->transform->SetLocalPosition(glm::vec3(-0.25f, 0.2f, 0));
	cube2->SetMeshRenderer(cube2->AddComponent<MeshRenderer>());
	cube2->GetMeshRenderer()->SetMesh(gunMesh);
	//radioMat->SetShininess(256);

	cube2->setMaterial(radioMat);
	//cube2->AddComponent<AudioSource>()->SetMusic(AbstractGame::Instance()->GetResourceManager()->GetMusic("expmusic"));
	//cube2->GetComponent<AudioSource>()->PlayMusic();

	cube2->transform->Scale(glm::vec3(1.0f, 1.0f, 1.0f));
	cube2->AddComponent<KeyMoveComponent>();
	//cube2->setBehaviour(new KeysBehaviour());

	GameObject* plane = _world->Instantiate<GameObject>();
	plane->transform->SetLocalPosition(glm::vec3(0, -1, 0));
	plane->SetMeshRenderer(plane->AddComponent<MeshRenderer>());
	plane->GetMeshRenderer()->SetMesh(planeMeshDefault);
	plane->setMaterial(planeMat);
	plane->transform->Scale(glm::vec3(50, 50, 50));

	Light* l = _world->Instantiate<Light>();
	l->transform->SetLocalPosition(glm::vec3(-2, 2, 0));
	l->transform->Rotate(glm::radians(90.0f), glm::vec3(1, 0, 0));
	l->transform->Rotate(glm::radians(45.0f), glm::vec3(0, 1, 0));
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
