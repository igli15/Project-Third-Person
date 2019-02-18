#pragma once

#include "mge/core/World.hpp"
#include "rapidxml/rapidxml.hpp"

class GameObject;

class MainWorld : public World
{
public:
	MainWorld();
	
	//testing XML/Unity Pareser
	void LoadXmlWorld();
	void ParseGameObject(rapidxml::xml_node<>* node,GameObject* gameObject);
	void ParseChilderen(rapidxml::xml_node<>* node, GameObject* gameObject);

	GameObject* ConvertGameObject(rapidxml::xml_node<>* node, GameObject* gameObject);

	virtual void Initialize() override;
	virtual ~MainWorld();
};

