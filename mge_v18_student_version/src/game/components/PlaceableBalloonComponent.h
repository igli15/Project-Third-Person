#pragma once
#include "game/components/BalloonComponent.h"

class PlaceableBalloonComponent : public BalloonComponent
{
public:
	PlaceableBalloonComponent();
	virtual ~PlaceableBalloonComponent();

	// Inherited via XMLComponent
	virtual void Parse(rapidxml::xml_node<>* compNode) override;
	virtual void OnPainted(PlayerDataComponent* playerData) override;
};