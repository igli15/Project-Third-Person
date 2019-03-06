#pragma once
#include "mge/core/XMLComponent.h"

class RefillStationComponent :public XMLComponent
{
public:
	void Start();
	void Update();
	void OnTrigger(CollisionInfo* collisionInfo);

	RefillStationComponent();
	virtual ~RefillStationComponent();

	// Inherited via XMLComponent
	virtual void Parse(rapidxml::xml_node<>* compNode) override;
private:
	float m_inkGainRate = 0;
};

