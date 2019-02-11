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
	
	AbstractMaterial* brickMat = new TextureMaterial(resourceManager->LoadTexture(config::MGE_TEXTURE_PATH + "bricks.jpg", "brickTex", TextureType::DIFFUSE), nullptr);
	TextureMaterial* carMat = new TextureMaterial(resourceManager->LoadTexture(config::MGE_TEXTURE_PATH + "carTex.png", "carTex", TextureType::DIFFUSE) , nullptr);
	//AbstractMaterial* modelMat = new TextureMaterial(resourceManager->LoadTexture(config::MGE_TEXTURE_PATH + "jeepTex.jpg", "carTex", TextureType::DIFFUSE), nullptr);
	ColorMaterial* planeMat = new ColorMaterial();
	ColorMaterial* lightMat = new ColorMaterial();

	TextureMaterial* containerMat = new TextureMaterial(resourceManager->LoadTexture(config::MGE_TEXTURE_PATH + "container2.png", "containerDiffuse", TextureType::DIFFUSE), resourceManager->LoadTexture(config::MGE_TEXTURE_PATH + "container2_specular.png", "containerSpecular", TextureType::SPECULAR));
	TextureMaterial* stuffMat = new TextureMaterial(resourceManager->LoadTexture(config::MGE_TEXTURE_PATH + "stuffTex.png", "stuffDiffuse", TextureType::DIFFUSE), resourceManager->LoadTexture(config::MGE_TEXTURE_PATH + "stuffSpec.png", "stuffSpecular", TextureType::SPECULAR));

	resourceManager->RegisterMaterial(brickMat, "brickMat");
	resourceManager->RegisterMaterial(carMat, "carMat");
	//resourceManager->RegisterMaterial(modelMat, "modelMat");
	resourceManager->RegisterMaterial(planeMat, "planeMat");
	resourceManager->RegisterMaterial(lightMat, "lightMat");
	resourceManager->RegisterMaterial(containerMat, "containerMat");
	resourceManager->RegisterMaterial(stuffMat, "stuffMat");
}

void MainGame::CreateWorld()
{
	AbstractGame::CreateWorld();
}

