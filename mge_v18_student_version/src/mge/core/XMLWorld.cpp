#include "XMLWorld.h"

#include <fstream>
#include <streambuf>
#include "mge/config.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/ResourceManager.h"
#include "mge/core/Camera.hpp"
#include "mge/components/CameraComponent.h"
#include "mge/core/Light.hpp"
#include "mge/components/LightComponent.h"
#include "mge/core/Mesh.hpp"
#include "mge/components/MeshRenderer.h"
#include "mge/core/GameObject.hpp"
#include "mge/components/RigidBody.h"
#include "mge/components/CircleCollider.h"
#include "mge/components/RectangleCollider.h"

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

	std::cout << "PARSING LEVEL....." << std::endl;
	ParseGameObject(rootNode, _world);
}

void XMLWorld::ParseGameObject(rapidxml::xml_node<>* node, GameObject * gameObject)
{
	GameObject* currentNode = gameObject;

	//if it read GameObject
	if (strcmp(node->name(), "GameObject") == 0)
	{
		GameObject* newNode = ConvertGameObject(node, gameObject);
		ColorMaterial* defaultMat = dynamic_cast<ColorMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("whiteMat"));
		newNode->setMaterial(defaultMat);

		if (strcmp(node->first_node()->name(), "Components") == 0)
		{
			rapidxml::xml_node<>* compNode = node->first_node();
			for (rapidxml::xml_node<>* com = compNode->first_node(); com != nullptr; com = com->next_sibling())
			{
				ParseComponents(com, newNode);
			}
		}

		//awake and start manually after attaching all components...
		newNode->Awake();
		newNode->Start();

		//TODO Change this
		if (gameObject != this)
		{
			currentNode->add(newNode);
		}

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

	for (rapidxml::xml_attribute<>* a = node->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
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
			gameObject->transform->SetLocalPosition(pos);
		}
		else if (attributeName == "rotation")
		{
			glm::quat rot;
			//seperate the value into 4 floats anf buffer them to quaternion...
			sscanf(a->value(), "(%f,%f,%f,%f)", &rot.x, &rot.y, &rot.z, &rot.w);
			gameObject->transform->Rotate(glm::angle(rot), glm::axis(rot));
		}
		else if (attributeName == "scale")
		{
			glm::vec3 scale;
			//seperate the value into 3 floats anf buffer them to scale vector...
			sscanf(a->value(), "(%f,%f,%f)", &scale.x, &scale.y, &scale.z);
			gameObject->transform->Scale(scale);
		}
		else if (attributeName == "mesh")
		{
			Mesh* mesh = AbstractGame::Instance()->GetResourceManager()->GetMesh(a->value());
			gameObject->SetMeshRenderer(gameObject->AddComponent<MeshRenderer>());
			gameObject->GetMeshRenderer()->SetMesh(mesh);
		}
	}
	
	return gameObject;
}

void XMLWorld::Initialize()
{
}

void XMLWorld::ParseComponents(rapidxml::xml_node<>* com,GameObject* newNode) 
{
		if (strcmp(com->name(), "CameraComponent") == 0)
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
		else if (strcmp(com->name(), "RigidBodyComponent") == 0)
		{
			(newNode)->AddComponent<RigidBody>()->Parse(com);
			newNode->SetRigidBody(newNode->GetComponent<RigidBody>());
		}
		else if (strcmp(com->name(), "CircleCollider") == 0)
		{
			(newNode)->AddComponent<CircleCollider>()->Parse(com);
			std::cout << "READ CIRCLE COLLIDER" << std::endl;
		}
		else if (strcmp(com->name(), "RectangleCollider") == 0)
		{
			(newNode)->AddComponent<RectangleCollider>()->Parse(com);
		}
		else if (strcmp(com->name(), "ColorMaterial") == 0)
		{
			ColorMaterial* colorMat = nullptr;
			for (rapidxml::xml_attribute<>* a = com->first_attribute();
				a != nullptr;
				a = a->next_attribute())
			{
				std::string attributeName(a->name());
				std::string value(a->value());
				if (attributeName == "materialName")
				{
					colorMat = dynamic_cast<ColorMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial(value));
					if (colorMat == nullptr)
					{
						colorMat = new ColorMaterial();
						AbstractGame::Instance()->GetResourceManager()->RegisterMaterial(colorMat, value);
					}
				}
				else if (attributeName == "shininess")
				{
					colorMat->SetShineness(strtof(a->value(), 0));
				}
				else if (attributeName == "diffuseColor")
				{
					glm::vec3 color;
					sscanf(a->value(), "(%f,%f,%f)", &color.x, &color.y, &color.z);
					colorMat->SetDiffuseColor(color);
				}
			}

			newNode->setMaterial(colorMat);
		}
		else if (strcmp(com->name(), "TextureMaterial") == 0)
		{
			TextureMaterial* texMat = nullptr;
			for (rapidxml::xml_attribute<>* a = com->first_attribute();
				a != nullptr;
				a = a->next_attribute())
			{
				std::string attributeName(a->name());
				std::string value(a->value());
				if (attributeName == "materialName")
				{
					texMat = dynamic_cast<TextureMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial(value));
					if (texMat == nullptr)
					{
						texMat = new TextureMaterial(nullptr, nullptr, nullptr, nullptr);
						AbstractGame::Instance()->GetResourceManager()->RegisterMaterial(texMat, value);
					}
				}
				else if (attributeName == "shininess")
				{
					texMat->SetShininess(strtof(a->value(), 0));
				}
				else if (attributeName == "diffuseColor")
				{
					glm::vec3 color;
					sscanf(a->value(), "(%f,%f,%f)", &color.x, &color.y, &color.z);
					texMat->SetDiffuseColor(color);
				}
				else if (attributeName == "shininess")
				{
					texMat->SetShininess(strtof(a->value(), 0));
				}
				else if (attributeName == "emissionScale")
				{
					texMat->SetEmissionScale(strtof(a->value(), 0));
				}
				else if (attributeName == "diffuseTexture")
				{
					texMat->setDiffuseTexture(AbstractGame::Instance()->GetResourceManager()->GetTexture(value));
				}
				else if (attributeName == "specularTexture")
				{
					texMat->SetSpecularTexture(AbstractGame::Instance()->GetResourceManager()->GetTexture(value));
				}
				else if (attributeName == "emissionTexture")
				{
					texMat->SetEmissionTexture(AbstractGame::Instance()->GetResourceManager()->GetTexture(value));
				}
				else if (attributeName == "normalTexture")
				{
					texMat->SetNormalTexture(AbstractGame::Instance()->GetResourceManager()->GetTexture(value));
				}
			}

			newNode->setMaterial(texMat);
		}

}
