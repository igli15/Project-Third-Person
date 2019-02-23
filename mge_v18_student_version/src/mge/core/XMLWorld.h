#pragma once

#include "mge/core/World.hpp"
#include "rapidxml/rapidxml.hpp"

class XMLWorld : public World
{
public:
	XMLWorld();
	virtual ~XMLWorld(); 

	void LoadXmlWorld(const std::string& fileName);

	virtual void Initialize() override;
	virtual void ParseComponents(rapidxml::xml_node<>* componentNode, GameObject* newNode);

private :

	void ParseGameObject(rapidxml::xml_node<>* node, GameObject* gameObject);
	void ParseChilderen(rapidxml::xml_node<>* node, GameObject* gameObject);

	GameObject* ConvertGameObject(rapidxml::xml_node<>* node, GameObject* gameObject);
};

