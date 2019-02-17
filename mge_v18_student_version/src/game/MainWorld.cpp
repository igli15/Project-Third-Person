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


#include "rapidxml/rapidxml.hpp"
#include <fstream>
#include <streambuf>

MainWorld::MainWorld()
{

}


void MainWorld::LoadXmlWorld()
{
	std::ifstream myXml("mge/scene.xml");
	std::vector<char> buffer((std::istreambuf_iterator<char>(myXml)),std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	rapidxml::xml_document<> doc;
	doc.parse<0>(&buffer[0]);
	
	rapidxml::xml_node<>* rootNode = doc.first_node("root");


}

void MainWorld::ParseGameObject(rapidxml::xml_node<>* node, GameObject * gameObject)
{
	GameObject* currentNode = gameObject;

	std::cout << "Processing: " << gameObject->getName() << std::endl;

	//if it read GameObject
	if (strcmp(node->name(), "GameObject") == 0)
	{
		GameObject* newNode = ConverGameObject(node,gameObject);

		//TODO Change this
		if (gameObject != this)
		{
			currentNode->add(newNode);
		}

		std::cout << newNode->getName() << " is added to " << currentNode->getName()<<std::endl;

		currentNode = newNode;
	}

	ParseChilderen(node, currentNode);
}

void MainWorld::ParseChilderen(rapidxml::xml_node<>* node, GameObject * gameObject)
{
	for (rapidxml::xml_node<>* child = node->first_node();child != nullptr;child = child->next_sibling())
	{
		ParseGameObject(child, gameObject);
	}
}

GameObject* MainWorld::ConverGameObject(rapidxml::xml_node<>* node, GameObject * objNode)
{

	//just for testing
	GameObject* gameObject = Instantiate<GameObject>();
	ColorMaterial* defaultMat = dynamic_cast<ColorMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("whiteMat"));
	gameObject->setMaterial(defaultMat);

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
			sscanf(a->value(), "%f,%f,%f", &pos.x, &pos.y, &pos.z);
			gameObject->transform->SetLocalPosition(pos);
		}
		else if (attributeName == "rotation")
		{
			glm::quat rot;
			//seperate the value into 4 floats anf buffer them to quaternion...
			sscanf(a->value(), "%f,%f,%f,%f", &rot.x, &rot.y, &rot.z,&rot.w);
			gameObject->transform->Rotate(glm::angle(rot),glm::axis(rot));
		}
		else if (attributeName == "scale")
		{
			glm::vec3 scale;
			//seperate the value into 3 floats anf buffer them to scale vector...
			sscanf(a->value(), "%f,%f,%f", &scale.x, &scale.y, &scale.z);
			gameObject->transform->Scale(scale);
		}

	}

	return gameObject;

}

void MainWorld::Initialize()
{
	Mesh* planeMeshDefault = AbstractGame::Instance()->GetResourceManager()->GetMesh("planeMesh");
	Mesh* cubeMesh = AbstractGame::Instance()->GetResourceManager()->GetMesh("cubeMesh");;
	Mesh* Car = AbstractGame::Instance()->GetResourceManager()->GetMesh("carMesh");;
	Mesh* gunMesh = AbstractGame::Instance()->GetResourceManager()->GetMesh("testMesh");;

	AbstractMaterial* brickMat = AbstractGame::Instance()->GetResourceManager()->GetMaterial("brickMat");
	ColorMaterial* planeMat = dynamic_cast<ColorMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("planeMat"));
	planeMat->SetShineness(126);
	planeMat->SetDiffuseColor(glm::vec3(0.13f, 0.54f, 0.130f));
	ColorMaterial* lightMat = dynamic_cast<ColorMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("lightMat"));
	lightMat->SetDiffuseColor(glm::vec3(1, 1, 0.8f));

	TextureMaterial* containerMat = dynamic_cast<TextureMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("containerMat"));
	TextureMaterial* radioMat = dynamic_cast<TextureMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("stuffMat"));

	Camera* camera = Instantiate<Camera>();
	camera->transform->SetLocalPosition(glm::vec3(0, 22, 22));
	camera->transform->Rotate(glm::radians(-65.0f), glm::vec3(1, 0, 0));
	camera->GetCameraComponent()->SetFOV(60); //Set Camera Properties via its component
	_world->setMainCamera(camera);

	GameObject* cube2 = _world->Instantiate<GameObject>();
	cube2->transform->SetLocalPosition(glm::vec3(0.5, 0.0f, 4));
	cube2->SetMeshRenderer(cube2->AddComponent<MeshRenderer>());
	cube2->GetMeshRenderer()->SetMesh(gunMesh);
	//radioMat->SetShininess(256);

	GameObject* canvas = _world->Instantiate<GameObject>();
	canvas->AddComponent<CanvasComponent>();
	canvas->Awake();

	GameObject* sprite = _world->Instantiate<GameObject>();
	sprite->AddComponent<UISpriteRenderer>()->ApplyTexture(AbstractGame::Instance()->GetResourceManager()->GetSFMLTexture("brickTex"));
	sprite->Awake();

	cube2->setMaterial(radioMat);
	/*cube2->AddComponent<AudioSource>()->SetMusic(AbstractGame::Instance()->GetResourceManager()->GetMusic("expmusic"));
	cube2->GetComponent<AudioSource>()->PlayMusic();
	cube2->GetComponent<AudioSource>()->PlayOneShotSound("cannonShot");
	*/
	cube2->transform->Scale(glm::vec3(1.0f,1.0f, 1.0f));
	cube2->AddComponent<KeyMoveComponent>();
	//cube2->setBehaviour(new KeysBehaviour());


	/*
	GameObject* cube = _world->Instantiate<GameObject>();
	cube->transform->SetLocalPosition(glm::vec3(0, 16, 19));
	//cube->transform->Rotate(glm::radians(45.0f),glm::vec3(1, 0,1));
	cube->SetMeshRenderer(cube->AddComponent<MeshRenderer>());
	cube->GetMeshRenderer()->SetMesh(cubeMesh);
	cube->AddComponent<RotatingComponent>();
	cube->setMaterial(containerMat);
	*/

	/*
	GameObject* goodBoy = _world->Instantiate<GameObject>();
	goodBoy->transform->SetLocalPosition(glm::vec3(0, 20, 21));
	//goodBoy->transform->Scale(glm::vec3(2,5,2));
	goodBoy->SetMeshRenderer(goodBoy->AddComponent<MeshRenderer>());
	goodBoy->GetMeshRenderer()->SetMesh(AbstractGame::Instance()->GetResourceManager()->GetMesh("goodBoyMesh"));
	goodBoy->AddComponent<RotatingComponent>();

	goodBoy->setMaterial(AbstractGame::Instance()->GetResourceManager()->GetMaterial("goodBoyMat"));
	*/

	Light* l = _world->Instantiate<Light>();
	l->transform->SetLocalPosition(glm::vec3(0, 19,19));
	l->transform->Rotate(glm::radians(90.0f), glm::vec3(1, 0, 0));
	l->transform->Rotate(glm::radians(45.0f), glm::vec3(0, 1, 1));
	l->GetLightComponent()->SetType(LightType::DIRECTIONAL);
	l->GetLightComponent()->SetIntensity(1.0f);
	l->GetLightComponent()->SetColor(glm::vec3(1, 1, 0.95f));
	l->GetLightComponent()->SetSpecularContribution(1.0f);
	l->GetLightComponent()->SetAttenuationConstants(glm::vec3(1, 0.7f, 1.8f));
	l->SetMeshRenderer(l->AddComponent<MeshRenderer>());
	l->GetMeshRenderer()->SetMesh(cubeMesh);
	l->setMaterial(lightMat);
	l->transform->Scale(glm::vec3(0.2f, 0.2f, 0.2f));

	Light* l2 = _world->Instantiate<Light>();
	l2->transform->SetLocalPosition(glm::vec3(2, 2, 0));
	l2->transform->Rotate(glm::radians(90.0f), glm::vec3(1, 0, 0));
	l2->transform->Rotate(glm::radians(45.0f), glm::vec3(0, 1, 0));
	l2->GetLightComponent()->SetType(LightType::POINT);
	l2->GetLightComponent()->SetColor(glm::vec3(1, 1, 0.8f));
	l2->GetLightComponent()->SetSpecularContribution(0.4f);
	l2->GetLightComponent()->SetAttenuationConstants(glm::vec3(1, 0.7f, 1.8f));
	l2->SetMeshRenderer(l2->AddComponent<MeshRenderer>());
	l2->GetMeshRenderer()->SetMesh(cubeMesh);
	l2->setMaterial(lightMat);
	l2->transform->Scale(glm::vec3(0.2f, 0.2f, 0.2f));

	//l2->Destroy();
}

MainWorld::~MainWorld()
{

}
