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

MainWorld::MainWorld()
{

}


void MainWorld::ParseComponents(rapidxml::xml_node<>* componentNode, GameObject * newNode)
{

	XMLWorld::ParseComponents(componentNode, newNode);

	if (strcmp(componentNode->name(), "GridComponent") == 0)
	{
		std::cout << "Parsing Grid Component...." << std::endl;
		for (rapidxml::xml_attribute<>* a = componentNode->first_attribute();
			a != nullptr;
			a = a->next_attribute())
		{
			std::cout << a->name() << " : " << a->value() << std::endl;
		}

	}
}

void MainWorld::Initialize()
{
	LoadXmlWorld("scene.xml");
}

MainWorld::~MainWorld()
{

}
