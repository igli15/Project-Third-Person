#include "MainGame.h"
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
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/test/TestComponent.h"
#include "mge/components/CameraComponent.h"
#include "mge/core/Light.hpp"
#include "mge/components/LightComponent.h"
#include "mge/core/WorldManager.h"
#include "game/MainWorld.h"
#include "mge/core/ResourceManager.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void MainGame::LoadResources(ResourceManager * resourceManager)
{
	AbstractGame::LoadResources(resourceManager);
	resourceManager->LoadMesh(config::MGE_MODEL_PATH + "plane.obj", "planeMesh");
	resourceManager->LoadMesh(config::MGE_MODEL_PATH + "cube_smooth.obj", "cubeMesh");
	resourceManager->LoadMesh(config::MGE_MODEL_PATH + "Car.obj", "carMesh");
	resourceManager->LoadMesh(config::MGE_MODEL_PATH + "jeep.obj", "jeepMesh");
	resourceManager->LoadMesh(config::MGE_MODEL_PATH + "stuff.obj", "testMesh");
}

void MainGame::Initialize()
{
	AbstractGame::Initialize();
}

