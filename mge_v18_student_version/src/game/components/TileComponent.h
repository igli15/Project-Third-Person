#pragma once
#include "mge/core/XMLComponent.h"
#include "glm.hpp"

class GridComponent;
class BalloonComponent;
class GridElement;

enum TileType
{
	LAVA,
	ICE,
	DEFAULT
};

class TileComponent : public XMLComponent
{
public:
	TileComponent();
	virtual ~TileComponent();

	void Parse(rapidxml::xml_node<>* compNode) override;

	void SetGridPos(glm::ivec2 gridPos);
	glm::ivec2 GridPos();

	bool IsPainted();
	bool IsPaintable();

	void SetTileType(TileType newType);
	TileType GetTileType();

	void PaintTile(TileType type);
	void SetGrid(GridComponent* grid);

	void SetGridElement(GridElement* gridElement);
	void RemoveGridElement(GridElement* gridElement);

	void ActivateGridElement(TileType type);
	
	//returns if it has a grid element on it or not
	bool IsFree();

private:

	GridComponent* m_grid;
	glm::ivec2 m_gridPos;
	TileType m_tileType = TileType::DEFAULT;
	bool m_isPainted = false;
	bool m_isPaintable = true;

	GridElement* m_gridElement = nullptr;
};

