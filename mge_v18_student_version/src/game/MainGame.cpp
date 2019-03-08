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
#include "mge/core/PlayerPrefs.h"
#include "tweeny/tweeny.h"
#include "game\MenuScene.h"
#include "game/ResolutionScreen.h"

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

	TextureMaterial* initMat = new TextureMaterial(resourceManager->GetTexture("iceDiffuse"), resourceManager->GetTexture("iceDiffuse"),nullptr,nullptr);

	ColorMaterial* whiteColor = new ColorMaterial();
	whiteColor->SetDiffuseColor(glm::vec3(1, 1, 1));


	resourceManager->RegisterMaterial(whiteColor, "whiteMat");
}

void MainGame::CreateWorld()
{
	std::cout << "Creating WORLD" << std::endl;
	std::cout << std::endl << "				SETING LEVEL_INDEX" << std::endl;
	PlayerPrefs::SetInt("LevelIndex", 1);
	AbstractGame::CreateWorld();

	//Loading an XML parsed world
	//Don't forget to call The "LoadXMLWorld" function.


	//XMLWorld* world = m_worldManager->CreateWorld<XMLWorld>("UNITYWORLD");
	//world->LoadXmlWorld("scene.xml");

	//Main World is now an XMLWorld...
	//PlayerPrefs::SetInt("test", 10);
	//PlayerPrefs::Clear("test");
	//m_worldManager->CreateWorld<MainWorld>("MainWorld");
	//std::cout << "Testing PlayerPrefs: " << PlayerPrefs::GetInt("test") << std::endl;

	//m_worldManager->CreateWorld<IlyasWorld>("IlyasWorld");
	//m_worldManager->CreateWorld<MenuScene>("MenuScene");

	//m_eventQueue->RegisterEvent<TestEvent>([](EventType* t) {std::cout << dynamic_cast<TestEvent*>(t)->test << std::endl; });
	//TestEvent* t = new TestEvent();
	//t->test = "TTTTT";
	//m_eventQueue->QueueEventType(t);
}

