#pragma once

#include "mge/core/World.hpp"
#include "rapidxml/rapidxml.hpp"

class GameObject;

class MainWorld : public World
{
public:
	MainWorld();

	virtual void Initialize() override;
	virtual ~MainWorld();
};

