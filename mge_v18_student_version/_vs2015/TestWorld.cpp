#include "TestWorld.h"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/World.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/test/TestComponent.h"
#include "mge/components/CameraComponent.h"
#include "mge/core/Light.hpp"
#include "mge/components/LightComponent.h"

TestWorld::TestWorld()
{
}


TestWorld::~TestWorld()
{
}

void TestWorld::initialize()
{
	AbstractGame::initialize();
}

void TestWorld::_initializeScene()
{
	Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
	Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_smooth.obj");
	Mesh* suzanaMesh = Mesh::load(config::MGE_MODEL_PATH + "suzanna_smooth.obj");

	AbstractMaterial* brickMat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg"));
	AbstractMaterial* planeMat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"));
	AbstractMaterial* colorMat = new ColorMaterial();

	


	Camera* camera = _world->Instantiate<Camera>();
	camera->transform->SetLocalPosition(glm::vec3(0, 4, 6));
	camera->transform->Rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
	camera->GetCameraComponent()->SetFOV(60); //Set Camera Properties via its component
	_world->setMainCamera(camera);

	GameObject* cube = _world->Instantiate<GameObject>();
	cube->transform->SetLocalPosition(glm::vec3(0,0,0));
	cube->SetMeshRenderer(cube->AddComponent<MeshRenderer>());
	cube->GetMeshRenderer()->SetMesh(cubeMesh);
	cube->setMaterial(brickMat);
	cube->setBehaviour(new KeysBehaviour(30));

	Light* l = _world->Instantiate<Light>();
	l->transform->SetLocalPosition(glm::vec3(0, 1, 0));
	l->GetLightComponent()->SetType(LightType::DIRECTIONAL);
	l->GetLightComponent()->SetSpecularContribution(0.4f);
	l->GetLightComponent()->SetAttenuationConstants(glm::vec3(1, 0.2f, 1.0f));
}
