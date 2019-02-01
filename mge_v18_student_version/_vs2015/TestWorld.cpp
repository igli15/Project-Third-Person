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

	Camera* camera = new Camera("camera", glm::vec3(0, 6, 7));
	camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
	_world->add(camera);
	_world->setMainCamera(camera);

	GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
	plane->scale(glm::vec3(5, 5, 5));
	plane->setMesh(planeMeshDefault);
	plane->setMaterial(planeMat);
	_world->add(plane);

	GameObject* suzana = new GameObject("suzana", glm::vec3(0, 1, 0));
	suzana->setMesh(suzanaMesh);
	suzana->setMaterial(colorMat);
	_world->add(suzana);

	GameObject* cube = new GameObject("cube", glm::vec3(0, 2, 0));
	cube->setMesh(cubeMesh);
	cube->setMaterial(brickMat);
	cube->setBehaviour(new KeysBehaviour(30));
	cube->add(camera);
	_world->add(cube);
}
