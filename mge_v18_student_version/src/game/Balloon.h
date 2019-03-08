#pragma once

#include "mge/core/GameObject.hpp"

class BalloonComponent;

class Balloon : public GameObject
{

public:
	Balloon();
	virtual ~Balloon();

	void Load() override;

	BalloonComponent* GetBalloonComponent();

private:

	BalloonComponent* m_balloonComponent;
};

