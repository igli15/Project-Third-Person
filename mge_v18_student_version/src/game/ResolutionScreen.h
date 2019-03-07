#pragma once
#include "mge/core/XMLWorld.h"
#include "mge/core/World.hpp"
class ResolutionScreen : public World
{

public:
	ResolutionScreen();
	virtual ~ResolutionScreen();
	virtual void Initialize() override;
};

