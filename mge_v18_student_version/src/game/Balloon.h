#pragma once

#include "mge/core/GameObject.hpp"
#include "mge/core/Tweener.h"
#include "tweeny/tweeny.h"

class BalloonComponent;

class Balloon : public GameObject
{

public:
	Balloon();
	virtual ~Balloon();

	void Load() override;
	void Update(float timeStep) override; 

	void OnDestroy() override;

	void ScaleUp();
	BalloonComponent* GetBalloonComponent();

private:

	BalloonComponent* m_balloonComponent;

	tweeny::tween<float, float, float>* m_scaleTween = nullptr;
};

