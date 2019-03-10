#pragma once
#include "mge/core/XMLComponent.h"
#include "TileComponent.h"

class GridComponent;
class TileComponent;
class PlayerDataComponent;

class GridElement : public XMLComponent
{

public:
	GridElement();
	virtual ~GridElement();

	void Awake() override;

	virtual void OnPainted(PlayerDataComponent* playerData);

	// Inherited via XMLComponent
	virtual void Parse(rapidxml::xml_node<>* compNode) override;

	void SetTile(TileComponent* tile);
	void SetGrid(GridComponent* grid);


protected:
	GridComponent* m_grid;
	TileComponent* m_tile;
};

