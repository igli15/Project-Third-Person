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
#include "game/components/GridComponent.h"
#include"game/components/TileComponent.h"

MainWorld::MainWorld()
{

}


void MainWorld::ParseComponents(rapidxml::xml_node<>* componentNode, GameObject * newNode)
{
	/*
		parses mge related components under the hood.
		do not forget to put this line!!
	*/
	XMLWorld::ParseComponents(componentNode, newNode);

	//Parse your game related components here.
	if (strcmp(componentNode->name(), "GridComponent") == 0)
	{
		newNode->AddComponent<GridComponent>()->Parse(componentNode);
		levelGrid = newNode->GetComponent<GridComponent>();
	}
	else if (strcmp(componentNode->name(), "TileComponent") == 0)
	{
		newNode->AddComponent<TileComponent>()->Parse(componentNode);
		levelGrid->AddTile(newNode->GetComponent<TileComponent>());
		std::cout << "Added Tile At Pos: " << newNode->transform->WorldPosition()<< std::endl;
	}
}

void MainWorld::Initialize()
{
	
	//Load the xml world.
	LoadXmlWorld("scene.xml");

	std::cout << "tile Pos is: " << levelGrid->GetTileAt(0, 7)->GetGameObject()->transform->WorldPosition()<<std::endl;
}

MainWorld::~MainWorld()
{

}
