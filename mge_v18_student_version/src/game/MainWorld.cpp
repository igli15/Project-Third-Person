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
		//std::cout << "Added Tile At Pos: " << newNode->transform->WorldPosition()<< std::endl;
	}
}

void MainWorld::Initialize()
{
	
	//Load the xml world.
	LoadXmlWorld("scene.xml");

	//std::cout << "tile Pos is: " << levelGrid->GetTileAt(0, 7)->GetGameObject()->transform->WorldPosition()<<std::endl;
	//Get tile pos and destroy it based on a "test position"
	std::cout << "tile Pos is: " << levelGrid->GetTilePlayerIsOn(glm::vec3(15,0,15))->GetGameObject()->transform->WorldPosition() << std::endl;
	std::cout << "tile Index is: " << levelGrid->GetTilePlayerIsOn(glm::vec3(15, 0, 15))->GridPos() << std::endl;
	//levelGrid->GetTilePlayerIsOn(glm::vec3(15, 0, 15))->GetGameObject()->Destroy();

	//to test if neighbour tile works..
	/*
	auto tiles = levelGrid->GetNeighbourTiles(glm::vec3(15, 0, 15),4,true,false);

	for (size_t i = 0; i < tiles.size(); i++)
	{
		tiles[i]->GetGameObject()->Destroy();
	}
	*/

	Player* player1 = Instantiate<Player>();
	player1->transform->Translate(glm::vec3(10, 6, 10));
	player1->transform->Scale(glm::vec3(5, 5, 5));
	player1->GetMeshRenderer()->SetMesh(AbstractGame::Instance()->GetResourceManager()->GetMesh("cylinderMesh"));
	player1->setMaterial(AbstractGame::Instance()->GetResourceManager()->GetMaterial("carMat"));
	player1->SetPlayerNumber(1);
	player1->GetComponent<ShootingComponent>()->SetGrid(levelGrid);
	//player1->GetComponent<PlayerMovementComponent>()->SetArenaData(glm::vec2(300, -200), glm::vec2(300, 200));
}

MainWorld::~MainWorld()
{

}

GridComponent * MainWorld::GetGrid() const
{
	return levelGrid;
}
