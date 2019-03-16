#pragma once

#include "mge/core/World.hpp"

class IlyasWorld : public World
{
public:
	IlyasWorld();

	virtual void Initialize() override;
	virtual ~IlyasWorld();
};

