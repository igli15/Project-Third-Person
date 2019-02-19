#include "XMLWorld.h"

#include <fstream>
#include <streambuf>
#include "mge/config.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/ResourceManager.h"
#include "mge/core/Camera.hpp"
#include "mge/components/CameraComponent.h"
#include "mge/core/Light.hpp"
#include "mge/components/LightComponent.h"
#include "mge/core/Mesh.hpp"
#include "mge/components/MeshRenderer.h"
#include "mge/core/GameObject.hpp"

XMLWorld::XMLWorld()
{
}


XMLWorld::~XMLWorld()
{
}

void XMLWorld::LoadXmlWorld(const std::string& fileName)
{
	std::ifstream myXml(config::MGE_SCENE_PATH + fileName);
	std::vector<char> buffer((std::istreambuf_iterator<char>(myXml)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	rapidxml::xml_document<> doc;
	doc.parse<0>(&buffer[0]);

	rapidxml::xml_node<>* rootNode = doc.first_node("root");

	ParseGameObject(rootNode, _world);
}

void XMLWorld::ParseGameObject(rapidxml::xml_node<>* node, GameObject * gameObject)
{
	GameObject* currentNode = gameObject;

	std::cout << "Processing: " << gameObject->getName() << std::endl;

	//if it read GameObject
	if (strcmp(node->name(), "GameObject") == 0)
	{
		

		GameObject* newNode = ConvertGameObject(node, gameObject);

		if (strcmp(node->first_node()->name(), "Components") == 0)
		{
			rapidxml::xml_node<>* compNode = node->first_node();
			std::cout << "Reading Components" << std::endl;
			for (rapidxml::xml_node<>* com = compNode->first_node(); com != nullptr; com = com->next_sibling())
			{
				std::cout << com->name() << std::endl;

				if (strcmp(com->name(), "TestComponent") == 0)
				{
					for (rapidxml::xml_attribute<>* a = com->first_attribute();
						a != nullptr;
						a = a->next_attribute())
					{
						std::cout << a->name() << " " << a->value() << std::endl;
					}
				}
				else if (strcmp(com->name(), "CameraComponent") == 0)
				{
					//gameObject->AddComponent<CameraComponent>()->Parse(com);
					(newNode)->AddComponent<CameraComponent>()->Parse(com);
					_world->setMainCamera(newNode->GetComponent<CameraComponent>());
				}
				else if (strcmp(com->name(), "LightComponent") == 0)
				{
					//gameObject->AddComponent<CameraComponent>()->Parse(com);
					(newNode)->AddComponent<LightComponent>()->Parse(com);
					registerLight(newNode->GetComponent<LightComponent>());
				}

			}
		}
		newNode->Awake();
		newNode->Start();

		//TODO Change this
		if (gameObject != this)
		{
			currentNode->add(newNode);
		}

		std::cout << newNode->getName() << " is added to " << currentNode->getName() << std::endl;

		currentNode = newNode;
	}

	ParseChilderen(node, currentNode);
}

void XMLWorld::ParseChilderen(rapidxml::xml_node<>* node, GameObject * gameObject)
{
	for (rapidxml::xml_node<>* child = node->first_node(); child != nullptr; child = child->next_sibling())
	{
		ParseGameObject(child, gameObject);
	}
}

GameObject * XMLWorld::ConvertGameObject(rapidxml::xml_node<>* node, GameObject * objNode)
{

	//just for testing
	GameObject* gameObject = Instantiate<GameObject>();
	ColorMaterial* defaultMat = dynamic_cast<ColorMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("whiteMat"));

	for (rapidxml::xml_attribute<>* a = node->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
		std::cout << a->name() << " = " << a->value() << std::endl;
		std::string attributeName = a->name();

		if (attributeName == "name")
		{
			gameObject->setName(a->value());
		}
		else if (attributeName == "position")
		{
			glm::vec3 pos;
			//seperate the value into 3 floats anf buffer them to pos vector...
			sscanf(a->value(), "(%f,%f,%f)", &pos.x, &pos.y, &pos.z);
			std::cout << "POs::::::: " << pos << std::endl;
			gameObject->transform->SetLocalPosition(pos);
		}
		else if (attributeName == "rotation")
		{
			glm::quat rot;
			//seperate the value into 4 floats anf buffer them to quaternion...
			sscanf(a->value(), "(%f,%f,%f,%f)", &rot.x, &rot.y, &rot.z, &rot.w);
			std::cout << "Rot::::::: " << rot << std::endl;
			gameObject->transform->Rotate(glm::angle(rot), glm::axis(rot));
		}
		else if (attributeName == "scale")
		{
			glm::vec3 scale;
			//seperate the value into 3 floats anf buffer them to scale vector...
			sscanf(a->value(), "(%f,%f,%f)", &scale.x, &scale.y, &scale.z);
			std::cout << "Scale::::::: " << scale << std::endl;
			gameObject->transform->Scale(scale);
		}
		else if (attributeName == "mesh")
		{
			Mesh* mesh = AbstractGame::Instance()->GetResourceManager()->GetMesh(a->value());
			std::cout << mesh->Vertices().size() << std::endl;
			gameObject->SetMeshRenderer(gameObject->AddComponent<MeshRenderer>());
			gameObject->GetMeshRenderer()->SetMesh(mesh);
		}
	}
	gameObject->setMaterial(defaultMat);

	return gameObject;
}

void XMLWorld::Initialize()
{
	/*
	Camera* camera = Instantiate<Camera>();
	camera->transform->SetLocalPosition(glm::vec3(0, 15, 10));
	camera->transform->Rotate(glm::radians(-65.0f), glm::vec3(1, 0, 0));
	camera->GetCameraComponent()->SetFOV(60); //Set Camera Properties via its component
	_world->setMainCamera(camera);
	

	Light* l = _world->Instantiate<Light>();
	l->transform->SetLocalPosition(glm::vec3(0, 19, 19));
	l->transform->Rotate(glm::radians(90.0f), glm::vec3(1, 0, 0));
	l->transform->Rotate(glm::radians(45.0f), glm::vec3(0, 1, 1));
	l->GetLightComponent()->SetType(LightType::DIRECTIONAL);
	l->GetLightComponent()->SetIntensity(1.0f);
	l->GetLightComponent()->SetColor(glm::vec3(1, 1, 0.95f));
	l->GetLightComponent()->SetSpecularContribution(1.0f);
	l->GetLightComponent()->SetAttenuationConstants(glm::vec3(1, 0.7f, 1.8f));
	l->SetMeshRenderer(l->AddComponent<MeshRenderer>());
	//l->GetMeshRenderer()->SetMesh(cubeMesh);
	//l->setMaterial(lightMat);
	l->transform->Scale(glm::vec3(0.2f, 0.2f, 0.2f));

	*/
}
