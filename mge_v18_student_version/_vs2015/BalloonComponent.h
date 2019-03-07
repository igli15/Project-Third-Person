#pragma once
#include "mge/core/XMLComponent.h"

class GridComponent;

class BalloonComponent : public XMLComponent
{
public:
	BalloonComponent();
	virtual ~BalloonComponent();

	void Awake();

private:

	GridComponent* m_grid;

};

