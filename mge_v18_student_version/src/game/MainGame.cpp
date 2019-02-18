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
#include "mge/eventTypes/TestEvent.h"
#include "mge/core/EventQueue.h"
#include <iostream>
#include "mge/core/XMLWorld.h"

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

	AbstractMaterial* brickMat = new TextureMaterial(resourceManager->GetTexture("brickTex"), nullptr,nullptr);
	TextureMaterial* carMat = new TextureMaterial(resourceManager->GetTexture("carTex"), nullptr, nullptr);
	
	ColorMaterial* planeMat = new ColorMaterial();
	ColorMaterial* lightMat = new ColorMaterial();

	ColorMaterial* whiteColor = new ColorMaterial();
	whiteColor->SetDiffuseColor(glm::vec3(1, 1, 1));

	TextureMaterial* containerMat = new TextureMaterial(resourceManager->GetTexture("containerDiffuse"),resourceManager->GetTexture("containerSpecular"), resourceManager->GetTexture("matrix"));
	TextureMaterial* stuffMat = new TextureMaterial(resourceManager->GetTexture("buildingTex"),resourceManager->GetTexture("buildingSpec"), nullptr);

	TextureMaterial* wallMat = new TextureMaterial(resourceManager->GetTexture("brickWall"), nullptr,nullptr, resourceManager->GetTexture("brickWallNormal"));
	TextureMaterial* wallMatNON = new TextureMaterial(resourceManager->GetTexture("brickWall"), nullptr, nullptr, nullptr);

	TextureMaterial* goodBoyMat = new TextureMaterial(resourceManager->GetTexture("goodBoyDiffuse"), nullptr, resourceManager->GetTexture("goodBoyEmission"), nullptr);

	resourceManager->RegisterMaterial(brickMat, "brickMat");
	resourceManager->RegisterMaterial(carMat, "carMat");
	resourceManager->RegisterMaterial(planeMat, "planeMat");
	resourceManager->RegisterMaterial(lightMat, "lightMat");
	resourceManager->RegisterMaterial(wallMat, "containerMat");
	resourceManager->RegisterMaterial(stuffMat, "stuffMat");
	resourceManager->RegisterMaterial(wallMatNON, "wallNON");
	resourceManager->RegisterMaterial(goodBoyMat, "goodBoyMat");
	resourceManager->RegisterMaterial(whiteColor, "whiteMat");
}

void MainGame::CreateWorld()
{
	AbstractGame::CreateWorld();
	//m_worldManager->CreateWorld<IlyasWorld>("IlyasWorld");

	//Loading an XML parsed world
	//Don't forget to call The "LoadXMLWorld" function.
	XMLWorld* world = m_worldManager->CreateWorld<XMLWorld>("UNITYWORLD");
	world->LoadXmlWorld("sceneTest.xml");


	//m_eventQueue->RegisterEvent<TestEvent>([](EventType* t) {std::cout << dynamic_cast<TestEvent*>(t)->test << std::endl; });
	//TestEvent* t = new TestEvent();
	//t->test = "TTTTT";
	//m_eventQueue->QueueEventType(t);
}

