#pragma once

#include "mge/core/World.hpp"

class MainWorld : public World
{
public:
	MainWorld();
	
	virtual void Initialize() override;
	virtual ~MainWorld();
};

