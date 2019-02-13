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
#include "mge/lua/LuaProgram.h"
#include "IlyasWorld.h"


MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void MainGame::LoadResources(ResourceManager * resourceManager)
{	
	AbstractGame::LoadResources(resourceManager);

	resourceManager->LoadResourcesFromLua();

	AbstractMaterial* brickMat = new TextureMaterial(resourceManager->GetTexture("brickTex"), nullptr);
	TextureMaterial* carMat = new TextureMaterial(resourceManager->GetTexture("carTex"), nullptr);
	
	ColorMaterial* planeMat = new ColorMaterial();
	ColorMaterial* lightMat = new ColorMaterial();

	TextureMaterial* containerMat = new TextureMaterial(resourceManager->GetTexture("containerDiffuse"),resourceManager->GetTexture("containerSpecular"));
	TextureMaterial* stuffMat = new TextureMaterial(resourceManager->GetTexture("buildingTex"),resourceManager->GetTexture("buildingSpec"));

	resourceManager->RegisterMaterial(brickMat, "brickMat");
	resourceManager->RegisterMaterial(carMat, "carMat");
	resourceManager->RegisterMaterial(planeMat, "planeMat");
	resourceManager->RegisterMaterial(lightMat, "lightMat");
	resourceManager->RegisterMaterial(containerMat, "containerMat");
	resourceManager->RegisterMaterial(stuffMat, "stuffMat");
}

void MainGame::CreateWorld()
{
	AbstractGame::CreateWorld();
	m_worldManager->CreateWorld<IlyasWorld>("IlyasWorld");
}

