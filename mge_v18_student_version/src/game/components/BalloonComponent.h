#pragma once
#include "game/components/GridElement.h"



class BalloonComponent : public GridElement
{

public:
	BalloonComponent();
	virtual ~BalloonComponent();

	virtual void Parse(rapidxml::xml_node<>* compNode) override;

	void Awake();
	
	void Explode(TileType type);

	void OnDestroy() override;

	virtual void OnPainted(PlayerDataComponent* playerData) override;

private:
	bool m_exploded = false;


};

