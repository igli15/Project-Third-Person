#pragma once

#include "mge/core/XMLWorld.h"

#include "rapidxml/rapidxml.hpp"
#include <fstream>
#include <streambuf>


class GameObject;
class GridComponent;

class MainWorld : public XMLWorld
{
public:
	MainWorld();

	void ParseComponents(rapidxml::xml_node<>* componentNode, GameObject* newNode) override;
	virtual void Initialize() override;
	virtual ~MainWorld();

private:
	GridComponent* levelGrid = nullptr;
};

