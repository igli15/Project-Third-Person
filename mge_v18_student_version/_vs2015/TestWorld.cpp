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
	AbstractMaterial* colorMat = new ColorMaterial(glm::vec3(0, 1, 1));

	Camera* camera = _world->Instantiate<Camera>();
	camera->transform->SetLocalPosition(glm::vec3(0, 4, 6));
	camera->transform->Rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
	_world->setMainCamera(camera);

	GameObject* cube = _world->Instantiate<GameObject>();
	cube->transform->SetLocalPosition(glm::vec3(0,0,0));
	cube->setMesh(cubeMesh);
	cube->setMaterial(brickMat);
	cube->setBehaviour(new KeysBehaviour(30));

}
