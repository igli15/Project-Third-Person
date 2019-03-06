#pragma once
#include "mge/core/XMLWorld.h"
#include "mge/core/World.hpp"


class MenuScene : public World
{
public:
	MenuScene();
	virtual ~MenuScene();
	virtual void Initialize() override;

};

