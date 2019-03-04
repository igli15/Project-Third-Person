#pragma once
#include "mge/core/XMLComponent.h"
#include "glm.hpp"

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

	void SetTileType(TileType newType);
	TileType GetTileType();

	void PaintTile(TileType type);

private:
	glm::ivec2 m_gridPos;
	TileType m_tileType = TileType::DEFAULT;
	bool m_isPainted = false;
	bool m_isPaintable = true;
};

