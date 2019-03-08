#pragma once
#include "mge/core/XMLComponent.h"
#include "TileComponent.h"

class GridComponent;
class TileComponent;

class GridElement : public XMLComponent
{

public:
	GridElement();
	virtual ~GridElement();

	void Awake() override;

	virtual void OnPainted(TileType type);

	// Inherited via XMLComponent
	virtual void Parse(rapidxml::xml_node<>* compNode) override;

	void SetTile(TileComponent* tile);



protected:
	GridComponent* m_grid;
	TileComponent* m_tile;
};

