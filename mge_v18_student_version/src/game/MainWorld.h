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

	GridComponent* GetGrid() const;

	void AddPlayer(GameObject* player);
	GameObject* GetPlayer(int playerNumber);

private:
	GridComponent* levelGrid = nullptr;

	int playerNumber = 2;

	std::vector<GameObject*> m_players;
};

