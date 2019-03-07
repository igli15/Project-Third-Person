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
#include "game/Player.h"
#include "game/components/ShootingComponent.h"
#include "HUD.h"

MainWorld::MainWorld()
{
	for (size_t i = 0; i < playerNumber; i++)
	{
		m_players.push_back(nullptr);
	}
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
		newNode->AddComponent<TileComponent>()->SetGrid(levelGrid);
		newNode->GetComponent<TileComponent>()->Parse(componentNode);
		levelGrid->AddTile(newNode->GetComponent<TileComponent>());
		
		//std::cout << "Added Tile At Pos: " << newNode->transform->WorldPosition()<< std::endl;
	}
	else if (strcmp(componentNode->name(), "PlayerMovement") == 0)
	{
		newNode->AddComponent<PlayerMovementComponent>()->Parse(componentNode);
	}
	else if (strcmp(componentNode->name(), "PlayerData") == 0)
	{
		std::cout << "Player Pos is:  " << newNode->transform->LocalPosition() << std::endl;
		newNode->AddComponent<PlayerDataComponent>()->Parse(componentNode);
		m_players[newNode->GetComponent<PlayerDataComponent>()->GetPlayerNumber() - 1] = newNode;
		
	}
	else if (strcmp(componentNode->name(), "ShootingComponent") == 0)
	{
		newNode->AddComponent<ShootingComponent>()->Parse(componentNode);
		newNode->GetComponent<ShootingComponent>()->SetGrid(levelGrid);
	}
	
}

void MainWorld::Initialize()
{

	GameObject* canvas = Instantiate<GameObject>();
	SetCanvas(canvas->AddComponent<CanvasComponent>());

	HUD* hud = Instantiate<HUD>();
	//Load the xml world.
	int currentLevelIndex = 2;
	switch (currentLevelIndex)
	{
	case 1:
		LoadXmlWorld("scene.xml");
		break;
	case 2:
		LoadXmlWorld("scene2.xml");
			break;
	case 3:
		LoadXmlWorld("scene2.xml");
		break;
	default:
		std::cout << "Cant find level with index: " + currentLevelIndex << std::endl;
		break;
	}



	//std::cout << "tile Pos is: " << levelGrid->GetTileAt(0, 7)->GetGameObject()->transform->WorldPosition()<<std::endl;
	//Get tile pos and destroy it based on a "test position"
//	std::cout << "tile Pos is: " << levelGrid->GetTileOnPos(glm::vec3(15,0,15))->GetGameObject()->transform->WorldPosition() << std::endl;
	//std::cout << "tile Index is: " << levelGrid->GetTileOnPos(glm::vec3(15, 0, 15))->GridPos() << std::endl;
	//levelGrid->GetTilePlayerIsOn(glm::vec3(15, 0, 15))->GetGameObject()->Destroy();

	//to test if neighbour tile works..
	/*
	auto tiles = levelGrid->GetNeighbourTiles(glm::vec3(100, 0, 100),4,false,false);

	for (size_t i = 0; i < tiles.size(); i++)
	{
		tiles[i]->GetGameObject()->Destroy();
	}
	*/
	/*
	auto tiles = levelGrid->GetTilesInARange(glm::vec3(20, 0, 20), glm::vec3(0, 0, 0), 4, 4, []() {});

	for (size_t i = 0; i < tiles.size(); i++)
	{
		tiles[i]->GetGameObject()->Destroy();
	}
	*/
	//player1->GetComponent<PlayerMovementComponent>()->SetArenaData(glm::vec2(300, -200), glm::vec2(300, 200));
}

MainWorld::~MainWorld()
{

}

GridComponent * MainWorld::GetGrid() const
{
	return levelGrid;
}

void MainWorld::AddPlayer(GameObject * player)
{
	m_players.push_back(player);
}

GameObject * MainWorld::GetPlayer(int playerNumber)
{
	return m_players.at(playerNumber);
}
